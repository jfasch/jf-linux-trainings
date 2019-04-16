#ifndef JF__WORK_QUEUE_H
#define JF__WORK_QUEUE_H

#include "shared-queue.h"

#include <functional>
#include <thread>


namespace jf {

class WorkQueue
{
public:
    using Work = std::function<void()>;
public:
    WorkQueue();
    ~WorkQueue();

    std::thread::id id() const { return thread_.get_id(); }

    void enqueue(Work);

private:
    std::thread thread_;
    SharedQueue<Work> queue_;
};

}

#endif
