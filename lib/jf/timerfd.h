#ifndef JF__TIMERFD_H
#define JF__TIMERFD_H

#include "fd.h"
#include "timespec.h"

#include <stdint.h>
#include <time.h>


namespace jf {

/** Wrapper around periodic timerfd

    See timerfd_create(2), timerfd_settime(2), ...
 */
class PeriodicTimerFD : public FD
{
public:
    PeriodicTimerFD(timespec interval);
    PeriodicTimerFD(timespec initial, timespec interval);

    uint64_t reap_expirations();

    void start();
    void stop();

private:
    timespec _initial;
    timespec _interval;
};

}

#endif
