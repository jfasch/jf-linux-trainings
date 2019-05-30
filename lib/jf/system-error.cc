#include "system-error.h"

#if ! _GNU_SOURCE
#  error nix _GNU_SOURCE
#endif
#include <cstring>

namespace jf {

SystemError::SystemError(int errnum)
: errnum_(errnum)
{
    char buffer[128];
    errstr_ = ::strerror_r(errnum, buffer, sizeof(buffer));
}

}
