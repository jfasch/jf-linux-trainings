#include "graceful-termination.h"

#include "system-error.h"

#include <cassert>
#include <cerrno>


namespace jf {

static SignalFD _setup(
    const std::vector<int>& signals)
{
    sigset_t set;
    sigemptyset(&set);
    for (int sig: signals)
        sigaddset(&set, sig);

    // block signals. if we do not block them then they get handled
    // using the default actions (most likely, terminating the
    // process)
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1)
        throw SystemError(errno, "sigprocmask, setting up graceful termination");

    return SignalFD(set);
}

GracefulTermination::GracefulTermination(
    const std::vector<int>& signals)
: signalfd_(_setup(signals)),
  requested_(false)
{}

}
