#include "precompiled.hh"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <unordered_map>

#include "defer.hh"

#include "rpc.hh"

namespace Steam {
Pipe *clientPipe;
Pipe *serverPipe;

Pipe *ClientPipe() {
    return clientPipe;
}
void SetClientPipe(Pipe *newPipe) {
    clientPipe = newPipe;
}
Pipe *ServerPipe() {
    return serverPipe;
}
void SetServerPipe(Pipe *newPipe) {
    serverPipe = newPipe;
}

class Semaphore {
    std::mutex              mtx;
    std::condition_variable cv;
    int                     count;

public:
    Semaphore(int count = 0)
        : count(count) {}

    inline void notify() {
        std::unique_lock<std::mutex> lock(mtx);
        count += 1;
        cv.notify_one();
    }

    inline void wait() {
        std::unique_lock<std::mutex> lock(mtx);

        while (count == 0) cv.wait(lock);
        count -= 1;
    }

    template <typename r, typename p>
    inline bool wait_for(std::chrono::duration<r, p> d) {
        std::unique_lock<std::mutex> lock(mtx);

        if (count == 1 || cv.wait_for(lock, d) == std::cv_status::no_timeout) {
            count -= 1;
            return true;
        } else {
            Assert(count == 0, "count should ALWAYS equal 0");
            return false;
        }
    }
};

namespace JobManager {
std::atomic<i64> jobCount        = 0;
std::atomic<i64> nonCallJobCount = 0;

std::unordered_map<i64, Semaphore> waitMap;
std::unordered_map<i64, Buffer>    resultMap;

// TODO: should these job ids just be the same
// And then we send the job type header every time?

i64 GetNextNonCallJobId() {
    return --nonCallJobCount;
}

i64 GetNextJobId() {
    return ++jobCount;
}

void PostResult(i64 jobId, Buffer &result) {
    resultMap[jobId] = result;

    // Some jobs may not have a semaphore i.e. async callresults
    if (waitMap.find(jobId) != waitMap.end())
        waitMap[jobId].notify();
}

bool HasResult(i64 jobId) {
    return resultMap.find(jobId) != resultMap.end();
}

Buffer FetchResult(i64 jobId) {
    // TODO should we do this?
    Assert(HasResult(jobId));

    Defer(resultMap.erase(jobId));
    return resultMap[jobId];
}

static std::chrono::seconds responseTimeout;

Buffer MakeCall(Buffer &data, Pipe::Target handle, Pipe &p, bool hasReturn) {
    i64 thisJob = GetNextJobId();

    data.Write(thisJob);

    p.SendMessage(handle, data);

    if (!hasReturn) return {};

    auto gotResult = waitMap[thisJob].wait_for(responseTimeout);
    waitMap.erase(thisJob);

    if (gotResult) {
        Defer(resultMap.erase(thisJob));
        return resultMap[thisJob];
    }

    // We didnt get a result in time (our pipe is probably broken (definitely probably broken))
    // this is a minor problem for everyone involved and there is going to be some
    // disapointment - but we have to bear with and get back to them with a result

    // TODO: raise IpcFailure_t
    LOG_F(ERROR, "!! Rpc pipe is broken\n");

    // Return an empty buffer that signals that we didnt get a result from the pipe
    return {};
}

void SetResponseTimeout(int seconds) {
    responseTimeout = std::chrono::seconds(seconds);
}

} // namespace JobManager

Buffer RpcBase::MakeRpcCall(Buffer &serializedArgs, Pipe::Target handle, Pipe &p, u32 dispatchPosition, bool hasReturn, Steam::UserHandle userHandle) {
    serializedArgs.SetPos(0);

    RpcCallHeader h{target, dispatchPosition, targetIndex, userHandle};
    serializedArgs.Write(h);

    serializedArgs.SetPos(0);

    return JobManager::MakeCall(serializedArgs, handle, p, hasReturn);
}

// SSA to ensure that the vector is initialised before being used.
std::vector<std::pair<void *, const char *>> &RpcDispatches() {
    static std::vector<std::pair<void *, const char *>> dispatches;
    return dispatches;
}
} // namespace Steam