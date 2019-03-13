#include "socketpair.h"

#include <cassert>
#include <sys/types.h>
#include <sys/socket.h>


namespace jf {
namespace linuxish {

SocketPair::SocketPair()
{
    int ends[2];
    int error = socketpair(AF_UNIX, SOCK_STREAM, 0, ends);
    assert(!error);

    _left = FD(ends[0]);
    _right = FD(ends[1]);
}

}
}
