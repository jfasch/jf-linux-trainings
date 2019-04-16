#ifndef JF__FD_H
#define JF__FD_H

#include <unistd.h>


namespace jf {

class FD
{
public:
    FD() : fd_(-1) {}
    explicit FD(int fd);
    ~FD();

    FD(FD&& fd)
    : fd_(fd.fd_)
    {
        fd.fd_ = -1;
    }
    FD& operator=(FD&& fd)
    { 
        fd_ = fd.fd_;
        fd.fd_ = -1;
        return *this;
    }

    int fd() const { return fd_; }
    operator int() const { return fd_; }

    ssize_t read(void* buf, size_t count);
    ssize_t write(const void *buf, size_t count);
    void close();

private:
    int fd_;
};

}

#endif
