#ifndef JF__SIGNALFD_H
#define JF__SIGNALFD_H

#include "fd.h"

#include <signal.h>
#include <sys/signalfd.h>


namespace jf {

class SignalFD
{
public:
    SignalFD(const sigset_t&);
    void wait(signalfd_siginfo&);

    const FD& fd() { return fd_; }

private:
    FD fd_;
};
    
}

#endif
