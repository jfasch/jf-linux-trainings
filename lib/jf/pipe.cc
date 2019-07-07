#include "pipe.h"

#include "system-error.h"

#include <unistd.h>
#include <errno.h>


namespace jf {

Pipe::Pipe()
{
    int ends[2];
    int ret = ::pipe(ends);
    if (ret == -1)
        throw SystemError(errno, "pipe()");

    reader_ = FD(ends[0]);
    writer_ = FD(ends[1]);
}

}
