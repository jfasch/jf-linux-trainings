#ifndef JF__SYSTEM_ERROR_H
#define JF__SYSTEM_ERROR_H

#include "system-error.h"

#include <string>


namespace jf {

class SystemError : public std::exception
{
public:
    SystemError(int errnum /*a.k.a. errno*/);
    virtual const char* what() const noexcept { return errstr_.c_str(); }
private:
    int errnum_;
    std::string errstr_;
};

}

#endif
