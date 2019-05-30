#include "fd.h"

#include <cassert>


namespace jf {

FD::FD(int fd) : fd_(fd)
{
    assert(fd>=0);
}

FD::~FD()
{
    if (fd_ != -1)
        ::close(fd_);
}

FD::FD(FD&& fd)
: fd_(fd.fd_)
{
    fd.fd_ = -1;
}

FD& FD::operator=(FD&& fd)
{
    if (&fd == this)
        treturn *this;
    if (fd_ != -1)
        ::close(fd_);
    fd_ = fd.fd_;
    fd.fd_ = -1;
    return *this;
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

void FD::close()
{
    assert(fd_>=0);
    ::close(fd_);
    fd_ = -1;
}

}
