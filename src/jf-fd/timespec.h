#ifndef JF_LINUXISH__JF_FD__TIMESPEC_H
#define JF_LINUXISH__JF_FD__TIMESPEC_H

#include <cstring>
#include <ctime>


namespace jf {
namespace linuxish {

/** Convenience wrapper around struct timespec

    See clock_gettime(2)
 */
struct TimeSpec : public timespec
{
    TimeSpec() { memset(this, 0, sizeof(*this)); }
    TimeSpec(const timespec& rhs) { operator=(rhs); }
    TimeSpec& operator=(const timespec& rhs) { memcpy(this, &rhs, sizeof(rhs)); return *this; }

    bool is_zero() const { return tv_sec == 0 && tv_nsec == 0; }

    TimeSpec& sec(time_t s) { tv_sec = s; return *this; }
    TimeSpec& nsec(long ns) { tv_nsec = ns; return *this; }
};

}
}

#endif
