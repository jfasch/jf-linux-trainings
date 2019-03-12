#include "dispatcher.h"

#include <cassert>
#include <sys/select.h>
#include <errno.h>

namespace jf {
namespace linuxish {

Dispatcher::~Dispatcher()
{
    assert(in_handlers_.size()==0);
    assert(out_handlers_.size()==0);
}

void Dispatcher::watch_in(int fd, Handler h)
{
    std::pair<HandlerSet::iterator, bool> found =
        in_handlers_.insert(std::make_pair(fd, h));
    assert(found.second==true);
}

void Dispatcher::watch_out(int fd, Handler h)
{
    std::pair<HandlerSet::iterator, bool> found =
        out_handlers_.insert(std::make_pair(fd, h));
    assert(found.second==true);
}

void Dispatcher::unwatch_in(int fd)
{
    HandlerSet::iterator found = in_handlers_.find(fd);
    assert(found!=in_handlers_.end());
    in_handlers_.erase(found);
}

void Dispatcher::unwatch_out(int fd)
{
    HandlerSet::iterator found = out_handlers_.find(fd);
    assert(found!=out_handlers_.end());
    out_handlers_.erase(found);
}

void Dispatcher::dispatch()
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

    // save away handler sets for later usage as the live ones may be
    // changed during the callback phase. this should probably be
    // optimized a bit as this is done quite often.
    HandlerSet saved_in_handlers(in_handlers_);
    HandlerSet saved_out_handlers(out_handlers_);

    int retval = ::select(max_fd+1, &in_fds, &out_fds, NULL, NULL);
    assert(retval != -1);

    // call back notified fd-handlers. take care that, although an fd
    // is notified, its handler might get unregistered by others
    // during the callback phase.
    for (int fd=0; fd<=max_fd; fd++)
        if (FD_ISSET(fd, &in_fds)) {
            HandlerSet::const_iterator found = saved_in_handlers.find(fd);
            assert(found!=saved_in_handlers.end());
            if (in_handlers_.find(fd) != in_handlers_.end())
                found->second(fd);
        }
    for (int fd=0; fd<=max_fd; fd++)
        if (FD_ISSET(fd, &out_fds)) {
            HandlerSet::const_iterator found = saved_out_handlers.find(fd);
            assert(found!=saved_out_handlers.end());
            if (out_handlers_.find(fd) != out_handlers_.end())
                found->second(fd);
        }
}

}
}
