#ifndef JF_LINUXISH__JF_FD__FD_H
#define JF_LINUXISH__JF_FD__FD_H

#include <unistd.h>


namespace jf {
namespace linuxish {

class FD
{
public:
    explicit FD(int fd);
    FD(FD&& fd) : _fd(fd._fd) { fd._fd = -1; }

    FD& operator=(FD&& fd) { _fd = fd._fd; fd._fd = -1; return *this; }

    int fd() const { return _fd; }
    ssize_t read(void* buf, size_t count);
    ssize_t write(const void *buf, size_t count);

private:
    int _fd;
};

}
}

#endif
