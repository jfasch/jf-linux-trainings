#include "ip4.h"

#include "system-error.h"

#include <string.h>
#include <arpa/inet.h>


namespace jf {

IP4Address::BadAddress::BadAddress(
    const std::string& addr)
: what_("Bad address: ")
{
    what_ += addr;
}

IP4Address::IP4Address(
    const std::string& s)
{
    memset(&addr_, 0, sizeof(addr_));
    int retval = ::inet_pton(AF_INET, s.c_str(), &addr_);
    if (retval == 1) // ok
        return;
    if (retval == 0) // not a valid ipv4 address
        throw BadAddress(s);
    if (retval == -1)
        throw SystemError(errno, "inet_pton()");
}

}
