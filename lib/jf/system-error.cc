#include "system-error.h"

#if ! _GNU_SOURCE
#  error nix _GNU_SOURCE
#endif
#include <cstring>

namespace jf {

SystemError::SystemError(
    int errnum, 
    const std::string& message)
: errnum_(errnum),
  errstr_(message)
{
    errstr_ += ": ";
    char buf[64];
    errstr_ += ::strerror_r(errnum_, buf, sizeof(buf));
    ::sprintf(buf, " (%d)", errnum_);
    errstr_ += buf;
}

}
