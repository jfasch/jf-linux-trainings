#include <jf-eventloop/dispatcher.h>
#include <jf-fd/socketpair.h>

#include <boost/test/unit_test.hpp>


namespace {

using namespace jf::linuxish;

struct EventLoopFixture
{
    Dispatcher dispatcher;
};


BOOST_FIXTURE_TEST_SUITE(EventloopSuite, EventLoopFixture)

BOOST_AUTO_TEST_CASE(basic)
{
    bool seen = false;
    SocketPair channel;

    dispatcher.watch_out(channel.right(),
                         [&channel](int)
                         {
                             char dummy = 'x';
                             ssize_t nwritten = channel.right().write(&dummy, sizeof(dummy));
                             assert(nwritten == sizeof(dummy));
                         });
    dispatcher.watch_in(channel.left(), 
                        [&channel, &seen](int)
                        {
                            char dummy;
                            ssize_t nread = channel.left().read(&dummy, sizeof(dummy));
                            assert(nread == sizeof(dummy));
                            seen = true;
                        });

    while (! seen)
        dispatcher.dispatch();

    dispatcher.unwatch_in(channel.left());
    dispatcher.unwatch_out(channel.right());
}

BOOST_AUTO_TEST_SUITE_END()

}
