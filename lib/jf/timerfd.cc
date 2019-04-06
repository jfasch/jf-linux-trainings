#include "timerfd.h"

#include <sys/timerfd.h>
#include <cassert>
#include <cstring>


namespace jf {

// -----------------------------------------------------------
// internal helpers
static int _create_fd()
{
    int fd = timerfd_create(CLOCK_MONOTONIC, 0);
    assert(fd != -1);
    return fd;
}
static void _start_fd(int fd, timespec initial, timespec interval)
{
    itimerspec spec {
        interval,
        initial
    };
    int error = timerfd_settime(fd, 0, &spec, nullptr);
    assert(!error);
}
static void _stop_fd(int fd)
{
    itimerspec spec;
    memset(&spec, 0, sizeof(spec));
    int error = timerfd_settime(fd, 0, &spec, nullptr);
    assert(!error);
}

// -----------------------------------------------------------
// PeriodicTimerFD implementation
PeriodicTimerFD::PeriodicTimerFD(
    TimeSpec interval)
: FD(_create_fd()),
  _initial(interval),
  _interval(interval)
{
    assert(! interval.is_zero());
}

PeriodicTimerFD::PeriodicTimerFD(
    TimeSpec initial,
    TimeSpec interval)
: FD(_create_fd()),
  _initial(initial),
  _interval(interval)
{
    assert(! _initial.is_zero());
    assert(! _interval.is_zero());
}

void PeriodicTimerFD::start()
{
    _start_fd(fd(), _initial, _interval);
}

void PeriodicTimerFD::stop()
{
    _stop_fd(fd());
}

}
