#ifndef JF__SOCKETPAIR_H
#define JF__SOCKETPAIR_H

#include "fd.h"


namespace jf {

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

#endif
