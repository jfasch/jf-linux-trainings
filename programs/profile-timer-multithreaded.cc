#include "_timer.h"

#include <string>
#include <iostream>
#include <thread>
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
        timers.push_back(TimerWithStats(interval, num_iterations));

    std::vector<std::thread> threads;
    for (auto& timer: timers) {
        threads.emplace_back([&timer]() {
                                 timer.start();
                                 while (true) {
                                     switch (timer.wait_expire()) {
                                         case TimerWithStats::Continue::Yes:
                                             continue;
                                         case TimerWithStats::Continue::No:
                                             return;
                                     }
                                 }
                             });
    }

    for (auto& thread: threads)
        thread.join();

    print_stats(timers);
    return 0;
}
