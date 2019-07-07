#ifndef JF__CAN_H
#define JF__CAN_H

#include "fd.h"

#include <linux/can.h>
#include <string>


namespace jf {

class CAN_Raw : public FD
{
public:
    CAN_Raw(const std::string& ifacename);
};
    
}

#endif
