#ifndef JF_LINUXISH__JF_EVENTLOOP__EVENTLOOP_SELECT_H
#define JF_LINUXISH__JF_EVENTLOOP__EVENTLOOP_SELECT_H

#include "eventloop.h"

#include <map>

namespace jf {
namespace linuxish {

class EventLoop_Select : public EventLoop
{
public:
    virtual ~EventLoop_Select();

    virtual void watch_in(int fd, EventLoop::Handler);
    virtual void watch_out(int fd, EventLoop::Handler);

    virtual void unwatch_in(int fd);
    virtual void unwatch_out(int fd);

    virtual void run_one();

    size_t num_watch_in() const { return in_handlers_.size(); }
    size_t num_watch_out() const { return out_handlers_.size(); }

private:
    typedef std::map<int, EventLoop::Handler> HandlerSet;
    HandlerSet in_handlers_;
    HandlerSet out_handlers_;
};

}
}

#endif
