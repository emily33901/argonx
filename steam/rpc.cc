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
void  SetClientPipe(Pipe *newPipe) {
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
        count++;
        cv.notify_one();
    }

    inline void wait() {
        std::unique_lock<std::mutex> lock(mtx);

        while (count == 0) cv.wait(lock);
        count--;
    }
};

namespace JobManager {
std::atomic<i64> jobCount = 0;
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
    waitMap[jobId].notify();
}

Buffer MakeCall(Buffer &data, Pipe::Target handle, Pipe &p, bool hasReturn) {
    i64 thisJob = GetNextJobId();

    data.Write(thisJob);
    data.SetPos(0);

    p.SendMessage(handle, data.Read(0), data.Size());

    if (!hasReturn) return {};

    waitMap[thisJob].wait();
    waitMap.erase(thisJob);

    Defer(resultMap.erase(thisJob));
    return resultMap[thisJob];
}
} // namespace JobManager

Buffer RpcBase::MakeRpcCall(Buffer &serializedArgs, Pipe::Target handle, Pipe &p, u32 dispatchPosition, bool hasReturn, Steam::UserHandle userHandle) {
    serializedArgs.SetPos(0);

    // TODO: write userHandle
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