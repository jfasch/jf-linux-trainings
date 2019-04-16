#include "signalfd.h"

#include "exception.h"

#include <cassert>


namespace jf {

SignalFD::SignalFD(const sigset_t& signals)
{
    int fd = ::signalfd(-1, &signals, 0);
    if (fd == -1)
        throw ErrnoException(errno, "signalfd()");
    fd_ = FD(fd);
}

void SignalFD::wait(signalfd_siginfo& info)
{
    ssize_t nread = fd_.read(&info, sizeof(info));
    if (nread == -1)
        throw ErrnoException(errno, "signalfd.read");
    assert(nread==sizeof(info));
}

}
