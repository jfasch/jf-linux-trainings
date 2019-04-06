#ifndef JF__TIMERFD_H
#define JF__TIMERFD_H

#include "fd.h"
#include "timespec.h"

#include <time.h>


namespace jf {

/** Wrapper around periodic timerfd

    See timerfd_create(2), timerfd_settime(2), ...
 */
class PeriodicTimerFD : public FD
{
public:
    PeriodicTimerFD(TimeSpec interval);
    PeriodicTimerFD(TimeSpec initial, TimeSpec interval);

    void start();
    void stop();

private:
    TimeSpec _initial;
    TimeSpec _interval;
};

}

#endif
