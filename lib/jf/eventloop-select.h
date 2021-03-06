#ifndef JF__EVENTLOOP_SELECT_H
#define JF__EVENTLOOP_SELECT_H

#include "eventloop.h"

#include <map>

namespace jf {

class EventLoop_select : public EventLoop
{
public:
    virtual void watch_in(int fd, EventLoop::Handler);
    virtual void watch_out(int fd, EventLoop::Handler);

    virtual void unwatch_in(int fd);
    virtual void unwatch_out(int fd);

    virtual void run_one();

    size_t num_in() const { return in_handlers_.size(); }
    size_t num_out() const { return out_handlers_.size(); }

private:
    typedef std::map<int, EventLoop::Handler> HandlerSet;
    HandlerSet in_handlers_;
    HandlerSet out_handlers_;
};

}

#endif
