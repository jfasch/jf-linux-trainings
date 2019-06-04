#ifndef JF__TIMESPEC_H
#define JF__TIMESPEC_H

#include <cstring>
#include <ctime>


namespace jf {

inline bool is_zero(timespec t)
{
    return t.tv_sec == 0 && t.tv_nsec == 0;
}

/** Convenience wrapper around struct timespec

    See clock_gettime(2)
 */
struct TimeSpec : public timespec
{
    TimeSpec() { memset(this, 0, sizeof(*this)); }
    TimeSpec(const timespec& rhs) { operator=(rhs); }
    TimeSpec& operator=(const timespec& rhs) { memcpy(this, &rhs, sizeof(rhs)); return *this; }

    bool is_zero() const { return jf::is_zero(*this); }

    TimeSpec& sec(time_t s) { tv_sec = s; return *this; }
    TimeSpec& nsec(long ns) { tv_nsec = ns; return *this; }
};

}

#endif
