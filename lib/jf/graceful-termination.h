#ifndef JF__GRACEFUL_TERMINATION_H
#define JF__GRACEFUL_TERMINATION_H

#include "signalfd.h"

#include <vector>
#include <sys/signal.h>


namespace jf {

class GracefulTermination
{
public:
    GracefulTermination(const std::vector<int>& signals);

    const FD& fd() { return signalfd_.fd(); }
    void make_request() { requested_ = true; }
    bool requested() const { return requested_; }

private:
    SignalFD signalfd_;
    bool requested_;
};

}

#endif
