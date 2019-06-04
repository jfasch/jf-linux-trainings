#include <jf/eventloop-epoll.h>
#include <jf/shared-event-queue.h>

#include <boost/test/unit_test.hpp>

#include <thread>

#include <sys/types.h>
#include <sys/wait.h>


namespace {

BOOST_AUTO_TEST_SUITE(SharedEventQueueSuite)

BOOST_AUTO_TEST_CASE(basic)
{
    jf::EventLoop_epoll eventloop;
    
    jf::SharedEventQueue<unsigned int> queue;
    bool quit = false;
    int num_callbacks = 0;
    eventloop.watch_in(
        queue.fd(),
        [&queue, &quit, &num_callbacks](int /*fd*/, jf::EventLoop*)
        {
            num_callbacks++;
            auto data = queue.pop();
            if (data == 42)
                quit = true;
        });
    
    std::thread producer(
        [&queue]()
        {
            for (int i=1; i<=42; i++)
                queue.push(i);
        });

    while (!quit)
        eventloop.run_one();

    BOOST_REQUIRE_EQUAL(num_callbacks, 42);

    producer.join();
}

BOOST_AUTO_TEST_SUITE_END()

}
