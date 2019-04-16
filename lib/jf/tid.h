#ifndef JF__TID_H
#define JF__TID_H

#include <unistd.h>
#include <sys/syscall.h>


namespace jf {

static inline pid_t gettid()
{
    return syscall(SYS_gettid);
}

}

#endif
