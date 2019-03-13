#include <jf-eventloop/eventloop-select.h>
#include <jf-fd/socketpair.h>

#include <boost/test/unit_test.hpp>


namespace {

using namespace jf::linuxish;

BOOST_AUTO_TEST_SUITE(EventLoopSuite)

BOOST_AUTO_TEST_CASE(basic)
{
    EventLoop_Select eventloop;
    bool seen = false;
    SocketPair channel;

    eventloop.watch_out(
        channel.right(),
        [&channel](int, EventLoop*)
        {
            char dummy = 'x';
            ssize_t nwritten = channel.right().write(&dummy, sizeof(dummy));
            assert(nwritten == sizeof(dummy));
        });
    eventloop.watch_in(
        channel.left(), 
        [&channel, &seen](int, EventLoop*)
        {
            char dummy;
            ssize_t nread = channel.left().read(&dummy, sizeof(dummy));
            assert(nread == sizeof(dummy));
            seen = true;
        });

    while (! seen)
        eventloop.run_one();

    BOOST_REQUIRE(eventloop.num_watch_in() == 1);
    BOOST_REQUIRE(eventloop.num_watch_out() == 1);

    eventloop.unwatch_in(channel.left());
    eventloop.unwatch_out(channel.right());
}

BOOST_AUTO_TEST_CASE(unregister_while_in_callback)
{
    EventLoop_Select eventloop;
    bool seen = false;
    SocketPair channel;

    eventloop.watch_out(
        channel.right(),
        [&channel](int fd, EventLoop* eventloop)
        {
            char dummy = 'x';
            ssize_t nwritten = channel.right().write(&dummy, sizeof(dummy));
            assert(nwritten == sizeof(dummy));
            eventloop->unwatch_out(fd);
        });
    eventloop.watch_in(
        channel.left(), 
        [&channel, &seen](int fd, EventLoop* eventloop)
        {
            char dummy;
            ssize_t nread = channel.left().read(&dummy, sizeof(dummy));
            assert(nread == sizeof(dummy));
            seen = true;
            eventloop->unwatch_in(fd);
        });
    
    while (! seen)
        eventloop.run_one();

    BOOST_REQUIRE(eventloop.num_watch_in() == 0);
    BOOST_REQUIRE(eventloop.num_watch_out() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

}
