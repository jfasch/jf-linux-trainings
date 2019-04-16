#ifndef JF__EXCEPTION_H
#define JF__EXCEPTION_H

#include <exception>
#include <string>
#include <cstring>

namespace jf {

class ErrnoException : public std::exception
{
public:
    ErrnoException(int error, const std::string& message)
    : message_(message),
      error_(error)
    {
        message_ += ": ";
        char buf[64];
        message_ += ::strerror_r(error_, buf, sizeof(buf));
        ::sprintf(buf, " (%d)", error_);
        message_ += buf;
    }

    const char* what() const noexcept
    {
        return message_.c_str();
    }

    int error() const { return error_; }

private:
    std::string message_;
    int error_;
};

}

#endif
