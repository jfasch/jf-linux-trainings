#include <jf/eventloop-select.h>
#include <jf/eventloop-epoll.h>
#include <jf/socketpair.h>

#include <boost/test/unit_test.hpp>


namespace {

static void test_basic(jf::EventLoop& eventloop)
{
    bool seen = false;
    jf::SocketPair channel;

    eventloop.watch_out(
        channel.right(),
        [&channel](int, jf::EventLoop*)
        {
            char dummy = 'x';
            ssize_t nwritten = channel.right().write(&dummy, sizeof(dummy));
            assert(nwritten == sizeof(dummy));
        });
    eventloop.watch_in(
        channel.left(), 
        [&channel, &seen](int, jf::EventLoop*)
        {
            char dummy;
            ssize_t nread = channel.left().read(&dummy, sizeof(dummy));
            assert(nread == sizeof(dummy));
            seen = true;
        });

    while (! seen)
        eventloop.run_one();

    eventloop.unwatch_in(channel.left());
    eventloop.unwatch_out(channel.right());
}

static void test_unregister_while_in_callback(jf::EventLoop& eventloop)
{
    bool seen = false;
    jf::SocketPair channel;

    eventloop.watch_out(
        channel.right(),
        [&channel](int fd, jf::EventLoop* eventloop)
        {
            char dummy = 'x';
            ssize_t nwritten = channel.right().write(&dummy, sizeof(dummy));
            assert(nwritten == sizeof(dummy));
            eventloop->unwatch_out(fd);
        });
    eventloop.watch_in(
        channel.left(), 
        [&channel, &seen](int fd, jf::EventLoop* eventloop)
        {
            char dummy;
            ssize_t nread = channel.left().read(&dummy, sizeof(dummy));
            assert(nread == sizeof(dummy));
            seen = true;
            eventloop->unwatch_in(fd);
        });
    
    while (! seen)
        eventloop.run_one();
}


BOOST_AUTO_TEST_SUITE(EventLoopSuite)

BOOST_AUTO_TEST_CASE(basic__select)
{
    jf::EventLoop_select eventloop;
    test_basic(eventloop);

    BOOST_REQUIRE_EQUAL(eventloop.num_in(), 0);
    BOOST_REQUIRE_EQUAL(eventloop.num_out(), 0);
}
BOOST_AUTO_TEST_CASE(basic__epoll)
{
    jf::EventLoop_epoll eventloop;
    test_basic(eventloop);
    BOOST_REQUIRE_EQUAL(eventloop.num_notifiers(), 0);
}

BOOST_AUTO_TEST_CASE(unregister_while_in_callback__select)
{
    jf::EventLoop_select eventloop;
    test_unregister_while_in_callback(eventloop);
}
BOOST_AUTO_TEST_CASE(unregister_while_in_callback__epoll)
{
    jf::EventLoop_epoll eventloop;
    test_unregister_while_in_callback(eventloop);
}

BOOST_AUTO_TEST_SUITE_END()

}
