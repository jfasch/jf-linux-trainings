#include <jf-eventloop/dispatcher.h>
#include <jf-fd/socketpair.h>

#include <boost/test/unit_test.hpp>


namespace {

using namespace jf::linuxish;

BOOST_AUTO_TEST_SUITE(EventloopSuite)

BOOST_AUTO_TEST_CASE(basic)
{
    Dispatcher dispatcher;
    bool seen = false;
    SocketPair channel;

    dispatcher.watch_out(channel.right(),
                         [&channel](int, Dispatcher*)
                         {
                             char dummy = 'x';
                             ssize_t nwritten = channel.right().write(&dummy, sizeof(dummy));
                             assert(nwritten == sizeof(dummy));
                         });
    dispatcher.watch_in(channel.left(), 
                        [&channel, &seen](int, Dispatcher*)
                        {
                            char dummy;
                            ssize_t nread = channel.left().read(&dummy, sizeof(dummy));
                            assert(nread == sizeof(dummy));
                            seen = true;
                        });

    while (! seen)
        dispatcher.dispatch();

    BOOST_REQUIRE(dispatcher.num_watch_in() == 1);
    BOOST_REQUIRE(dispatcher.num_watch_out() == 1);

    dispatcher.unwatch_in(channel.left());
    dispatcher.unwatch_out(channel.right());
}

BOOST_AUTO_TEST_CASE(unregister_while_in_callback)
{
    Dispatcher dispatcher;
    bool seen = false;
    SocketPair channel;

    dispatcher.watch_out(channel.right(),
                         [&channel](int fd, Dispatcher* dispatcher)
                         {
                             char dummy = 'x';
                             ssize_t nwritten = channel.right().write(&dummy, sizeof(dummy));
                             assert(nwritten == sizeof(dummy));
                             dispatcher->unwatch_out(fd);
                         });
    dispatcher.watch_in(channel.left(), 
                        [&channel, &seen](int fd, Dispatcher* dispatcher)
                        {
                            char dummy;
                            ssize_t nread = channel.left().read(&dummy, sizeof(dummy));
                            assert(nread == sizeof(dummy));
                            seen = true;
                            dispatcher->unwatch_in(fd);
                        });

    while (! seen)
        dispatcher.dispatch();

    BOOST_REQUIRE(dispatcher.num_watch_in() == 0);
    BOOST_REQUIRE(dispatcher.num_watch_out() == 0);
}

BOOST_AUTO_TEST_SUITE_END()

}
