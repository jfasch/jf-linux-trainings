#include <jf/tcp4.h>

#include <boost/test/unit_test.hpp>

#include <thread>


namespace {

std::shared_ptr<jf::TCP4Port> grab_available()
{
    std::shared_ptr<jf::TCP4Port> port;
    for (uint16_t portno=1024; portno<0xffffU; portno++)
        try {
            return std::make_shared<jf::TCP4Port>(portno);
        }
        catch (const jf::TCP4Port::EAddrInUse&) {
            continue;
        }
    return nullptr;
}

BOOST_AUTO_TEST_SUITE(TCP4Suite)

BOOST_AUTO_TEST_CASE(implicit_wildcard_address)
{
    auto port = grab_available();

    std::thread echo_server(
        [&port]()
        {
            jf::TCP4Connection client_connection = port->accept();
            char one_byte;
            ssize_t nread = client_connection.read(&one_byte, 1);
            assert(nread == 1);
            ++one_byte;
            ssize_t nwritten = client_connection.write(&one_byte, 1);
            assert(nwritten == 1);
            // terminate
        });

    jf::TCP4Connection connection("127.0.0.1", port->port_number());
    char one_byte = '7';
    ssize_t nwritten = connection.write(&one_byte, 1);
    BOOST_REQUIRE_EQUAL(nwritten, 1);
    ssize_t nread = connection.read(&one_byte, 1);
    BOOST_REQUIRE_EQUAL(nread, 1);
    BOOST_REQUIRE_EQUAL(one_byte, '8');

    echo_server.join();
}

BOOST_AUTO_TEST_CASE(todo)
{
    BOOST_REQUIRE(!"FD::read,write: unsigned, throw SystemError");
    BOOST_REQUIRE(!"NotAvailable is a system error, give it a better ctor");
    BOOST_REQUIRE(!"alternative TCP4Connection ctor (hostname resolution)");
    BOOST_REQUIRE(!"accept with peer address");
    BOOST_REQUIRE(!"alternative port ctor: explicit iface address");
}

BOOST_AUTO_TEST_SUITE_END()

}
