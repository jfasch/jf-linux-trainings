#ifndef JF__TCP4_H
#define JF__TCP4_H

#include "fd.h"
#include "system-error.h"

#include <string>
#include <cstdint>


namespace jf {

class TCP4Connection : public FD
{
public:
    TCP4Connection(int connection_fd) : FD(connection_fd) {}
    TCP4Connection(const std::string&, uint16_t port_number);
};

class TCP4Port
{
public:
    class EAddrInUse : public SystemError 
    {
    public:
        EAddrInUse(const std::string& message) : SystemError(EADDRINUSE, message) {}
    };

public:
    TCP4Port(uint16_t port_number);
    uint16_t port_number() const { return port_number_; }
    TCP4Connection accept();

private:
    FD port_fd_;
    uint16_t port_number_;
};

}

#endif
