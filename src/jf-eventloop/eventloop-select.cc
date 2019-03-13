#include "eventloop-select.h"

#include <cassert>
#include <sys/select.h>
#include <errno.h>


namespace jf {
namespace linuxish {

void EventLoop_select::watch_in(int fd, EventLoop::Handler h)
{
    std::pair<HandlerSet::iterator, bool> found =
        in_handlers_.insert(std::make_pair(fd, h));
    assert(found.second==true);
}

void EventLoop_select::watch_out(int fd, EventLoop::Handler h)
{
    std::pair<HandlerSet::iterator, bool> found =
        out_handlers_.insert(std::make_pair(fd, h));
    assert(found.second==true);
}

void EventLoop_select::unwatch_in(int fd)
{
    HandlerSet::iterator found = in_handlers_.find(fd);
    assert(found!=in_handlers_.end());
    in_handlers_.erase(found);
}

void EventLoop_select::unwatch_out(int fd)
{
    HandlerSet::iterator found = out_handlers_.find(fd);
    assert(found!=out_handlers_.end());
    out_handlers_.erase(found);
}

void EventLoop_select::run_one()
{
    int max_fd = 0;
    
    fd_set in_fds;
    FD_ZERO(&in_fds);
    for (HandlerSet::iterator i = in_handlers_.begin();
         i != in_handlers_.end();
         ++i) {
        FD_SET(i->first, &in_fds);
        max_fd = std::max(max_fd, i->first);
    }

    fd_set out_fds;
    FD_ZERO(&out_fds);
    for (HandlerSet::iterator i = out_handlers_.begin();
         i != out_handlers_.end();
         ++i) {
        FD_SET(i->first, &out_fds);
        max_fd = std::max(max_fd, i->first);
    }

    int retval = ::select(max_fd+1, &in_fds, &out_fds, NULL, NULL);
    assert(retval != -1);

    // call back notified fd-handlers. take care that, although an fd
    // is notified, its handler might get unregistered by others
    // during the callback phase.
    for (int fd=0; fd<=max_fd; fd++)
        if (FD_ISSET(fd, &in_fds)) {
            auto found = in_handlers_.find(fd);
            if (found != in_handlers_.end())
                found->second(fd, this);
        }
    for (int fd=0; fd<=max_fd; fd++)
        if (FD_ISSET(fd, &out_fds)) {
            auto found = out_handlers_.find(fd);
            if (found != out_handlers_.end())
                found->second(fd, this);
        }
}

}
}
