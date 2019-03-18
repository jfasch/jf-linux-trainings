#include "_timer.h"



TimerWithStats::Continue TimerWithStats::wait_expire() 
{ 
    uint64_t n_expiries;
    ssize_t nread = _timerfd.read(&n_expiries, sizeof(n_expiries));
    assert(nread == sizeof(n_expiries));

    _cur_expiries += n_expiries;

    size_t num_late = n_expiries - 1;

    // we are expecting 1 expiration per wakeup. if there have been
    // more, those are late.
    _stats.num_late += num_late;
    // max
    _stats.max_late = std::max(_stats.max_late, num_late);

    if (_cur_expiries >= _num_expiries)
    {
        _timerfd.stop();
        return Continue::No;
    }
    else
        return Continue::Yes;
}
