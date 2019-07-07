#include "signalfd.h"

#include "system-error.h"

#include <cassert>


namespace jf {

SignalFD::SignalFD(const sigset_t& signals)
{
    int fd = ::signalfd(-1, &signals, 0);
    if (fd == -1)
        throw SystemError(errno, "signalfd()");
    this->own(fd);
}

void SignalFD::wait(signalfd_siginfo& info)
{
    ssize_t nread = this->read(&info, sizeof(info));
    if (nread == -1)
        throw SystemError(errno, "signalfd.read");
    assert(nread==sizeof(info));
}

}
