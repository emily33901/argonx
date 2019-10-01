#pragma once

#include "buffer.hh"
#include "platform.hh"
#include "rpc.hh"

namespace Steam {
// Represents a very basic asynchronous job that can occur on the server
// It has no knowledge of what its result should be other than that it processes
// a callback and then posts the result to the job manager
struct AsyncJob {
    enum class Result {
        yield,  // Still waiting on something but passed control back
        finish, // Done
    };

    // Callback should be non-blocking
    // If you cannot compute the result right now (due to not having your
    // result back from steam etc... then you shoud return AsyncJobResult::yield)
    using Callback = Result (*)(const AsyncJob &b);

    // jobId this represents
    const i64 jobId;

    // Callback for this job
    Callback callback;

    // Returns AsyncJobResult so that you can write
    // `return b.Finish(Buffer{result});`
    Result Finish(Buffer &result) const {
        result.SetPos(0);
        JobManager::PostResult(jobId, result);
        return Result::finish;
    }

    Result RunJob() {
        return callback(*this);
    }
};

AsyncJob NewAsyncJob(AsyncJob::Callback callback);
void     RunAsyncJobs();
} // namespace Steam