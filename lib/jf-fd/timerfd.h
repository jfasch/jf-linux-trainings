#ifndef JF_LINUXISH__JF_FD__TIMERFD_H
#define JF_LINUXISH__JF_FD__TIMERFD_H

#include "fd.h"
#include "timespec.h"

#include <time.h>


namespace jf {
namespace linuxish {

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
}

#endif
