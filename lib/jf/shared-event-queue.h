#ifndef JF__SHARED_EVENT_QUEUE_H
#define JF__SHARED_EVENT_QUEUE_H

#include "shared-queue.h"
#include "eventfd.h"


namespace jf {

/// Producer/consumer queue, with file descriptor event notification
/// support

/** Works like SharedQueue<>, except that the consumer end provides a
    file descriptor for event notification. Register the file
    descriptor in an EventLoop, together with a callback, and you can
    use the queue in an event driven application.
 */
template<typename T> class SharedEventQueue {
public:
    SharedEventQueue(size_t maxelem = std::numeric_limits<size_t>::max());

    int fd() const { return eventfd_; }

    void push(const T&);
    T pop();

private:
    SharedQueue<T> queue_;
    EventFD eventfd_;
    std::mutex lock_;
};

template<typename T> SharedEventQueue<T>::SharedEventQueue(size_t maxelem) 
: queue_(maxelem) 
{
    eventfd_.set_nonblocking();
}

template<typename T> void SharedEventQueue<T>::push(const T& elem)
{
    queue_.push(elem);
    eventfd_.produce(1);
}

template<typename T> T SharedEventQueue<T>::pop()
{
    uint64_t num_announced = eventfd_.consume();
    T elem = queue_.pop_nowait();
    // we have seen num_announced elements, but consumed only
    // one. re-announced those that we did not consume.
    if (num_announced > 1)
        eventfd_.produce(num_announced-1);
    return elem;
}

}

#endif
