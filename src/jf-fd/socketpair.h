#ifndef JF_LINUXISH__JF_FD__SOCKETPAIR_H
#define JF_LINUXISH__JF_FD__SOCKETPAIR_H

#include "fd.h"


namespace jf {
namespace linuxish {

class SocketPair
{
public:
    SocketPair();

    FD& left() { return _left; }
    FD& right() { return _right; }

private:
    FD _left;
    FD _right;
};

}
}

#endif
