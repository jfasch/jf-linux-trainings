#include "_protocols.h"

#include <jf/posix-message-queue.h>


int main()
{
    jf::POSIXMessageQueue::create(
        "/ComponentA", O_RDWR, 0600, 
        jf::POSIXMessageQueue::Attr().set_maxmsg(5).set_msgsize(sizeof(message_A)));
    jf::POSIXMessageQueue::create(
        "/ComponentB", O_RDWR, 0600, 
        jf::POSIXMessageQueue::Attr().set_maxmsg(5).set_msgsize(sizeof(message_B)));
    return 0;
}
