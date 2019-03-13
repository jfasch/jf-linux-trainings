#include "fd.h"

#include <cassert>


namespace jf {
namespace linuxish {

FD::FD(int fd) : fd_(fd)
{
    assert(fd>=0);
}

FD::~FD()
{
    if (fd_ != -1)
        ::close(fd_);
}

ssize_t FD::read(void* buf, size_t count)
{
    assert(fd_>=0);
    return ::read(fd_, buf, count);
}

ssize_t FD::write(const void *buf, size_t count)
{
    assert(fd_>=0);
    return ::write(fd_, buf, count);
}

}
}
