#include "fd.h"

#include <cassert>


namespace jf {
namespace linuxish {

FD::FD(int fd) : _fd(fd)
{
    assert(fd>=0);
}

ssize_t FD::read(void* buf, size_t count)
{
    assert(_fd>=0);
    return ::read(_fd, buf, count);
}

ssize_t FD::write(const void *buf, size_t count)
{
    assert(_fd>=0);
    return ::write(_fd, buf, count);
}

}
}
