#include <jf/work-queue.h>
#include <jf/tid.h>

#include <boost/test/unit_test.hpp>

#include <atomic>
#include <chrono>
#include <thread>


using namespace std::chrono_literals;

namespace {

BOOST_AUTO_TEST_SUITE(WorkQueueSuite)

BOOST_AUTO_TEST_CASE(basic)
{
    jf::WorkQueue wq;
    std::atomic<std::thread::id> wq_id;

    auto work = [&wq_id](){ wq_id = std::this_thread::get_id(); };
    wq.enqueue(work);

    // spin until work done (no, this is not a real life use case :-)
    size_t num_spins = 100;
    while (wq_id == std::thread::id() && --num_spins)
        std::this_thread::sleep_for(50ms);

    BOOST_REQUIRE_NE(wq_id, std::thread::id()/*default ctor*/);

    // verify that work was done in a different thread
    BOOST_REQUIRE_NE(wq_id, std::this_thread::get_id());
    BOOST_REQUIRE_EQUAL(wq_id, wq.id());
}

BOOST_AUTO_TEST_SUITE_END()

}
