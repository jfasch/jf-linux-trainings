#include <jf/eventloop-epoll.h>
#include <jf/timerfd.h>
#include <jf/graceful-termination.h>

#include <iostream>


int main()
{
    try {
        jf::EventLoop_epoll loop;

        jf::GracefulTermination graceful_termination({SIGTERM, SIGINT, SIGQUIT});

        auto graceful_termination_callback = 
            [&graceful_termination](int, jf::EventLoop*) {
                graceful_termination.set_requested();
            };
        auto timer1_callback = 
            [&timer1](int, jf::EventLoop*) {
                std::cout << "Timer 1 expired " << timer1.reap_expirations() << " times" << std::endl;
            };
        auto timer2_callback = 
            [&timer2](int, jf::EventLoop*) {
                std::cout << "Timer 2 expired " << timer2.reap_expirations() << " times" << std::endl;
            };

        loop.watch_in(graceful_termination.fd(), graceful_termination_callback);
        loop.watch_in(timer1.fd(), timer1_callback);
        loop.watch_in(timer2.fd(), timer2_callback);

        timer1.start();
        timer2.start();

        // run
        while (! graceful_termination.requested())
            loop.run_one();
        std::cout << "Shutdown ..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
