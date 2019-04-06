#include "_timer.h"

#include <jf/eventloop-epoll.h>
#include <string>
#include <iostream>
#include <vector>


int main(int argc, char** argv)
{
    if (argc != 4) {
        std::cerr << argv[0] << " <num-timers> <num-iterations> <interval-ms>" << std::endl;
        exit(1);
    }

    size_t num_timers = std::stoul(argv[1]);
    size_t num_iterations = std::stoul(argv[2]);
    size_t interval_ms = std::stoul(argv[3]);

    timespec interval {
        /*sec*/ (long)(interval_ms / 1000),
        /*nsec*/ (long)((interval_ms % 1000) * 1000 * 1000)
    };

    std::vector<TimerWithStats> timers;
    while (num_timers--)
        timers.emplace_back(interval, num_iterations);

    jf::EventLoop_epoll eventloop;

    size_t num_active_timers = 0;
    for (auto& timer: timers) {
        num_active_timers++;
        timer.start();
        eventloop.watch_in(timer.fd(),
                           [&timer, &num_active_timers](int, jf::EventLoop*)
                           {
                               switch (timer.wait_expire()) {
                                   case TimerWithStats::Continue::Yes:
                                       break;
                                   case TimerWithStats::Continue::No:
                                       num_active_timers--;
                                       break;
                               }
                           }
        );
    }

    while (num_active_timers)
        eventloop.run_one();

    print_stats(timers);
    return 0;
}
