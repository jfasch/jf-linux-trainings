#include <jf/eventloop-epoll.h>
#include <jf/pipe.h>
#include <jf/graceful-termination.h>

#include <boost/test/unit_test.hpp>

#include <sys/types.h>
#include <sys/wait.h>


namespace {

BOOST_AUTO_TEST_SUITE(GracefulTerminationSuite)

BOOST_AUTO_TEST_CASE(basic)
{
    jf::Pipe pipe;

    pid_t pid = fork();
    assert(pid != -1);

    if (pid == 0 /*child*/) {
        pipe.close_reader();

        jf::EventLoop_epoll loop;
        jf::GracefulTermination termination({SIGTERM});
        loop.watch_in(termination.fd(), [&termination](int, jf::EventLoop*){termination.make_request();});

        // now being prepared for graceful; send handshake to my test.
        const char handshake_byte = 'h';
        ssize_t nwritten = pipe.writer().write(&handshake_byte, 1);
        assert(nwritten == 1);

        while (!termination.requested())
            loop.run_one();
        exit(0);
    }
    else /*parent - the unittest*/;

    // wait until child has installed signal handlers and whatnot.
    pipe.close_writer();
    char handshake_byte;
    ssize_t nread = pipe.reader().read(&handshake_byte, 1);
    assert(nread == 1);

    kill(pid, SIGTERM);

    int status;
    pid_t killed = waitpid(pid, &status, 0);
    BOOST_REQUIRE_EQUAL(killed, pid);
    BOOST_REQUIRE(WIFEXITED(status));
    BOOST_REQUIRE_EQUAL(WEXITSTATUS(status), 0);
}

BOOST_AUTO_TEST_SUITE_END()

}
