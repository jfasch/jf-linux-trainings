#ifndef JF__IP4_H
#define JF__IP4_H

#include <string>
#include <exception>
#include <netinet/in.h>


namespace jf {

class IP4Address
{
public:
    class BadAddress : public std::exception
    {
    public:
        BadAddress(const std::string& addr);
        virtual const char* what() const noexcept { return what_.c_str(); }
    private:
        std::string what_;
    };

public:
    IP4Address(const std::string&);
    operator in_addr() const { return addr_; }
private:
    in_addr addr_;
};

}

#endif
