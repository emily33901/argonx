#include "precompiled.hh"

#include <atomic>
#include <condition_variable>
#include <mutex>

#include <unordered_map>

#include "defer.hh"

#include "rpc.hh"

namespace Steam {
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

class JobManager : public JobManagerBase {
    std::atomic<u64> jobCount = 0;

    std::unordered_map<u64, Semaphore> waitMap;
    std::unordered_map<u64, Buffer>    resultMap;

public:
    virtual Buffer MakeCall(Buffer &data, Pipe::Handle handle, Pipe &p, bool hasReturn) {
        u64 thisJob = ++jobCount;

        data.Write(thisJob);
        data.SetPos(0);

        p.SendMessage(handle, data.Read(0), data.Size());

        if (!hasReturn) return {};

        waitMap[thisJob].wait();

        waitMap.erase(thisJob);

        Defer(resultMap.erase(thisJob));

        return resultMap[thisJob];
    }

    virtual void PostResult(u64 jobId, Buffer &result) {
        resultMap[jobId] = result;
        waitMap[jobId].notify();
    }
};

JobManagerBase *Jobs() {
    static JobManager j;
    return &j;
}

Buffer RpcBase::MakeRpcCall(Buffer &serializedArgs, Pipe::Handle handle, Pipe &p, int dispatchPosition, bool hasReturn) {
    serializedArgs.SetPos(0);

    // TODO: write userHandle
    RpcCallHeader h{target, dispatchPosition, targetIndex, 0};
    serializedArgs.Write(h);

    serializedArgs.SetPos(0);

    return Jobs()->MakeCall(serializedArgs, handle, p, hasReturn);
}

std::vector<std::pair<void *, const char *>> &RpcDispatches() {
    static std::vector<std::pair<void *, const char *>> dispatches;
    return dispatches;
}
} // namespace Steam