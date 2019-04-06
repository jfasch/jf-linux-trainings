#pragma once

#include <jf/timerfd.h>

#include <iostream>
#include <cassert>
#include <cstring>


class TimerWithStats
{
public:
    enum class Continue
    {
        Yes,
        No
    };

    struct Stats
    {
        Stats() { memset(this, 0, sizeof(*this)); }

        size_t num_late;
        size_t max_late;
    };

public:
    TimerWithStats(jf::TimeSpec interval, size_t num_expiries)
    : _timerfd(interval),
      _cur_expiries(0),
      _num_expiries(num_expiries) {}

    int fd() const { return _timerfd.fd(); }

    void start() { _timerfd.start(); }
    Continue wait_expire();

    Stats stats() const { return _stats; }

private:
    jf::PeriodicTimerFD _timerfd;
    size_t _cur_expiries;
    const size_t _num_expiries;

    Stats _stats;
};

template <typename Timers>
void print_stats(const Timers& timers)
{
    size_t max_late = 0;
    size_t accumulated_late = 0;
    for (const auto& timer: timers) {
        accumulated_late += timer.stats().num_late;
        max_late = std::max(max_late, timer.stats().max_late);
    }

    std::cout << "{\n";
    std::cout << "  'total_late': " << accumulated_late << ",\n";
    std::cout << "  'max_late': " << max_late << ",\n";
    std::cout << "}\n";
}
