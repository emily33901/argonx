#include <precompiled.hh>

#include "asyncjob.hh"

namespace Steam {

static std::vector<AsyncJob> jobs;

AsyncJob NewAsyncJob(AsyncJob::Callback callback) {
    auto jobId = JobManager::GetNextNonCallJobId();
    auto r     = AsyncJob{jobId, callback};

    jobs.push_back(r);

    return r;
}

void RunAsyncJobs() {
    std::vector<decltype(jobs.begin())> toRemove;

    for (auto it = jobs.begin(); it != jobs.end(); ++it) {
        const auto j      = *it;
        auto       result = j.RunJob();
        if (result == AsyncJob::Result::finish) {
            toRemove.push_back(it);
        }
    }

    // Now remove them from the jobs
    for (auto it : toRemove) {
        jobs.erase(it);
    }
}
} // namespace Steam