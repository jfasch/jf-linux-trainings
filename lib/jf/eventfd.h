#ifndef JF__EVENTFD_H
#define JF__EVENTFD_H

#include "fd.h"

#include <sys/eventfd.h>


namespace jf {

class EventFD : public FD
{
public:
    EventFD(unsigned int initval = 0, int flags = 0);

    void produce(uint64_t howmany);
    uint64_t consume();
};
    
}

#endif
