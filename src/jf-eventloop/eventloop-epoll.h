#ifndef JF_LINUXISH__JF_EVENTLOOP__EVENTLOOP_EPOLL_H
#define JF_LINUXISH__JF_EVENTLOOP__EVENTLOOP_EPOLL_H

#include "eventloop.h"

#include <jf-fd/fd.h>

#include <vector>
#include <map>
#include <cassert>
#include <sys/epoll.h>


namespace jf {
namespace linuxish {

class EventLoop_epoll : public EventLoop, public FD
{
public:
    EventLoop_epoll();

    virtual void watch_in(int fd, EventLoop::Handler);
    virtual void watch_out(int fd, EventLoop::Handler);

    virtual void unwatch_in(int fd);
    virtual void unwatch_out(int fd);

    virtual void run_one();

    size_t num_notifiers() const { return notifiers_.size(); }

private:
    struct Notifier {
        Handler in_handler;
        Handler out_handler;
    };
    typedef std::map<int, Notifier> Notifiers;
    Notifiers notifiers_;
    
    std::vector<epoll_event> events_;

    FD epoll_fd_;

private:
    epoll_event make_event_(Notifiers::iterator);
    Notifiers::iterator make_notifier_(int fd, int& epoll_op);
    void update_(Notifiers::iterator);
};

}
}

#endif
