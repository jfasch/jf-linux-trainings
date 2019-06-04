#include <jf/eventloop-epoll.h>
#include <jf/timerfd.h>
#include <jf/shared-event-queue.h>
#include <jf/graceful-termination.h>

#include <iostream>
#include <chrono>
#include <atomic>
#include <thread>

using namespace std::chrono_literals;


int main()
{
    try {
        jf::EventLoop_epoll loop;

        jf::GracefulTermination graceful_termination({SIGTERM, SIGINT, SIGQUIT});
        jf::PeriodicTimerFD timer(/*initial: 3s*/{1, 0}, /*interval: 3s*/{1, 0});
        jf::SharedEventQueue<int> ros_queue;

        auto graceful_termination_callback = 
            [&graceful_termination](int, jf::EventLoop*) {
                graceful_termination.set_requested();
            };
        auto timer_callback = 
            [&timer](int, jf::EventLoop*) {
                std::cout << "Timer expired " << timer.reap_expirations() << " times" << std::endl;
            };
        auto ros_callback = 
            [&ros_queue](int, jf::EventLoop*) {
                std::cout << "ROS has something to say: " << ros_queue.pop() << std::endl;
            };

        loop.watch_in(graceful_termination.fd(), graceful_termination_callback);
        loop.watch_in(timer.fd(), timer_callback);
        loop.watch_in(ros_queue.fd(), ros_callback);

        timer.start();

        // mimick ROS AsyncSpinner behaviour: he fires callbacks from
        // inside the context of a background thread. those callbacks
        // bounce their data into our ros_queue which is watched from
        // inside the main thread.
        std::atomic<bool> ros_quitflag;
        std::thread ros_thread([&ros_queue, &ros_quitflag]()
                               {
                                   int ros_msg = 0;
                                   while (!ros_quitflag) {
                                       std::this_thread::sleep_for(5s);
                                       ros_queue.push(ros_msg++);
                                   }
                               });

        // run
        while (! graceful_termination.requested())
            loop.run_one();
        std::cout << "Shutting down ROS ..." << std::endl;
        ros_quitflag = true;
        ros_thread.join();
        std::cout << "... bye" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
