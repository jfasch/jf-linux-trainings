#ifndef JF_LINUXISH__JF_EVENTLOOP__EVENTLOOP_H
#define JF_LINUXISH__JF_EVENTLOOP__EVENTLOOP_H

#include <functional>

namespace jf {
namespace linuxish {

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

    virtual size_t num_in() const = 0;
    virtual size_t num_out() const = 0;
};

}
}

#endif
