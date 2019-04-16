#include "work-queue.h"

#include <future>


namespace {
class Quit {};
}

namespace jf {

WorkQueue::WorkQueue()
{
    thread_ = std::thread(
        [this]() {
            while (true) {
                Work work = queue_.pop();
                try {
                    work();
                }
                catch (const Quit&) {
                    break;
                }
            }
        });

    // we want WorkerThread::id() to give the correct thread id once
    // ctor is over. synchronize with thread startup to ensure it has
    // been scheduled/initialized.
    std::promise<void> sync_promise;
    auto sync_future = sync_promise.get_future();
    queue_.push([&sync_promise]() { sync_promise.set_value(); });
    sync_future.get();
}

WorkQueue::~WorkQueue()
{
    queue_.push([](){throw Quit();});
    thread_.join();
}

void WorkQueue::enqueue(Work work)
{
    queue_.push(work);
}
    
};
