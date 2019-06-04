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

    FD(FD&&);
    FD& operator=(FD&&);

    void own(int fd);

    int fd() const { return fd_; }
    operator int() const { return fd_; }

    size_t read(void* buf, size_t count);
    size_t write(const void *buf, size_t count);
    void close();

    void set_nonblocking();

private:
    int fd_;
};

}

#endif
