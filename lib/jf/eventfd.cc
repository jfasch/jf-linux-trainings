#include "eventfd.h"

#include "system-error.h"

#include <cassert>


namespace jf {

EventFD::EventFD(
    unsigned int initval,
    int flags)
: FD(::eventfd(initval, flags))
{
    if (this->fd() == -1)
        throw SystemError(errno);
}

void EventFD::produce(uint64_t howmany)
{
    auto nwritten = this->write(&howmany, sizeof(howmany));
    // can't see why writing into an eventfd could fail
    assert(nwritten == sizeof(howmany));
}

uint64_t EventFD::consume()
{
    uint64_t howmany = 0; // valgrind cannot look into the kernel, so
                          // kindly initialize it.
    auto nread = this->read(&howmany, sizeof(howmany));
    // can't see why reading from an eventfd could fail
    assert(nread == sizeof(howmany));
    return howmany;
}

}
