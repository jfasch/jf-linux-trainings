#include "can.h"

#include "system-error.h"

#include <string.h>
#include <sys/ioctl.h>
#include <net/if.h>


namespace jf {

CAN_Raw::CAN_Raw(
    const std::string& ifacename)
{
    int fd;
    fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (fd == -1)
        throw SystemError(errno, "socket(PF_CAN, SOCK_RAW, CAN_RAW)");

    struct ifreq ifr;
    strcpy(ifr.ifr_name, ifacename.c_str());
    int error = ioctl(fd, SIOCGIFINDEX, &ifr);
    if (error) {
        std::string msg = "ioctl(SIOCGIFINDEX on ";
        msg += ifacename;
        msg += ')';
        throw SystemError(errno, msg);
    }

    this->own(fd);

    struct sockaddr_can addr;
    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    error = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (error)
        throw SystemError(errno, "bind()");
}
    
}
