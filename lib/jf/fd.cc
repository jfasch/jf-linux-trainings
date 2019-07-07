#include "fd.h"

#include "system-error.h"

#include <cassert>
#include <unistd.h>
#include <fcntl.h>


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
        return *this;
    if (fd_ != -1)
        ::close(fd_);
    fd_ = fd.fd_;
    fd.fd_ = -1;
    return *this;
}

void FD::own(int fd)
{
    if (fd_ != -1)
        ::close(fd_);
    fd_ = fd;
}

size_t FD::read(void* buf, size_t count)
{
    assert(fd_>=0);
    ssize_t nread = ::read(fd_, buf, count);
    if (nread == -1)
        throw SystemError(errno, "read()");
    return nread;
}

size_t FD::write(const void *buf, size_t count)
{
    assert(fd_>=0);
    ssize_t nwritten = ::write(fd_, buf, count);
    if (nwritten == -1)
        throw SystemError(errno, "write()");
    return nwritten;
}

void FD::close()
{
    assert(fd_>=0);
    ::close(fd_);
    fd_ = -1;
}

void FD::set_nonblocking()
{
    int flags = ::fcntl(fd_, F_GETFL, 0);
    if (flags == -1)
        throw SystemError(errno, "fcntl(F_GETFL)");

    if (flags & O_NONBLOCK)
        return;

    int error = ::fcntl(fd_, F_SETFL, flags | O_NONBLOCK);
    if (error)
        throw SystemError(errno, "fcntl(F_SETFL)");
}

}
