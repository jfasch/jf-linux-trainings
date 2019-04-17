#include <jf/posix-message-queue.h>

#include <boost/test/unit_test.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

namespace {

class RandomInit
{
public:
    RandomInit()
    {
        srandom(time(NULL));
    }
};
static RandomInit randominit;

class MyFixture
{
public:
    MyFixture()
    {
        char tmp[128];
        sprintf(tmp, "/POSIXMessageQueueSuite-%ld", random());
        mq_name = tmp;
    }
    ~MyFixture()
    {
        jf::POSIXMessageQueue::unlink(mq_name);
    }

    std::string mq_name;
};


BOOST_FIXTURE_TEST_SUITE(POSIXMessageQueueSuite, MyFixture)

BOOST_AUTO_TEST_CASE(basic)
{
    jf::POSIXMessageQueue mq_produce = 
        jf::POSIXMessageQueue::create(mq_name, O_WRONLY, 0600, 
                                      jf::POSIXMessageQueue::Attr().set_maxmsg(5).set_msgsize(1));
    jf::POSIXMessageQueue mq_consume = 
        jf::POSIXMessageQueue::open(mq_name, O_RDONLY);

    char msg_sent = 'a';
    mq_produce.send(&msg_sent, 1, 0);
    char  msg_received = 0; // valgrind has no idea what mq_receive()
                            // is
    size_t nread = mq_consume.receive_raw(&msg_received, 1);

    BOOST_REQUIRE_EQUAL(nread, 1);
    BOOST_REQUIRE_EQUAL(msg_received, 'a');
}

BOOST_AUTO_TEST_CASE(UnrelatedProcessesUsingSameMQ)
{
    // message queue created by one central authority. that authority
    // does not make use of it.
    jf::POSIXMessageQueue::create(mq_name, O_RDWR, 0600, 
                                  jf::POSIXMessageQueue::Attr().set_maxmsg(5).set_msgsize(1));

    pid_t producer = fork();
    if (producer == 0) { // child
        jf::POSIXMessageQueue mq_produce = jf::POSIXMessageQueue::open(mq_name, O_WRONLY);
        const char c = 'a'; 
        mq_produce.send(&c, 1, 0);
        _exit(0);
    }
    pid_t consumer = fork();
    if (consumer == 0) { // child
        jf::POSIXMessageQueue mq_consume = jf::POSIXMessageQueue::open(mq_name, O_RDONLY);
        char c = 0; // valgrind does not know about mq_receive()
        size_t nread = mq_consume.receive_raw(&c, 1);
        if (nread != 1)
            _exit(1);
        if (c != 'a')
            _exit(1);
        _exit(0);
    }

    int status;
    pid_t awaited;

    // reap producer
    awaited = waitpid(producer, &status, 0);
    BOOST_REQUIRE_EQUAL(awaited, producer);
    BOOST_REQUIRE(WIFEXITED(status));
    BOOST_REQUIRE_EQUAL(WEXITSTATUS(status), 0);

    // reap consumer
    awaited = waitpid(consumer, &status, 0);
    BOOST_REQUIRE_EQUAL(awaited, consumer);
    BOOST_REQUIRE(WIFEXITED(status));
    BOOST_REQUIRE_EQUAL(WEXITSTATUS(status), 0);
}

BOOST_AUTO_TEST_SUITE_END()

}
