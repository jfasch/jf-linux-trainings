#ifndef JF__EVENTLOOP_H
#define JF__EVENTLOOP_H

#include <functional>

namespace jf {

class EventLoop
{
public:
    using Handler = std::function<void(int/*fd*/, EventLoop*)>;
    
public:
    virtual ~EventLoop() {}

    virtual void watch_in(int fd, Handler) = 0;
    virtual void watch_out(int fd, Handler) = 0;

    virtual void unwatch_in(int fd) = 0;
    virtual void unwatch_out(int fd) = 0;

    virtual void run_one() = 0;
};

}

#endif
