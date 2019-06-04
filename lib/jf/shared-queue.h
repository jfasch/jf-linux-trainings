#ifndef JF__SHARED_QUEUE_H
#define JF__SHARED_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <limits>


namespace jf {

template<typename T> class SharedQueue {
public:
    class WouldBlock : public std::exception 
    {
    public:
        virtual const char* what() const noexcept { return "nothing there"; }
    };

public:
    SharedQueue(size_t maxelem = std::numeric_limits<size_t>::max());

    void push(const T&);
    T pop();
    T pop_nowait();

private:
    size_t maxelem_;
    std::queue<T> queue_;
    std::mutex lock_;
    std::condition_variable notfull_;
    std::condition_variable notempty_;
};

template<typename T> SharedQueue<T>::SharedQueue(size_t maxelem) 
: maxelem_(maxelem) {}

template<typename T> void SharedQueue<T>::push(const T& elem)
{
    {
        std::unique_lock<std::mutex> guard(lock_);
        while (queue_.size() == maxelem_)
            notfull_.wait(guard);
        queue_.push(elem);
    }
    notempty_.notify_one();
}

template<typename T> T SharedQueue<T>::pop()
{
    T elem;
    {
        std::unique_lock<std::mutex> guard(lock_);
        while (queue_.size() == 0)
            notempty_.wait(guard);
        elem = queue_.front();
        queue_.pop();
    }
    notfull_.notify_one();
    return elem;
}

template<typename T> T SharedQueue<T>::pop_nowait()
{
    T elem;
    {
        std::unique_lock<std::mutex> guard(lock_);
        if (queue_.size() == 0)
            throw WouldBlock();
        elem = queue_.front();
        queue_.pop();
    }
    notfull_.notify_one();
    return elem;
}

}

#endif
