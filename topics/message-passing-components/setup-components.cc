#include "_protocols.h"

#include <jf/posix-message-queue.h>


int main()
{
    jf::POSIXMessageQueue::create(
        queue_name_A, O_RDWR|O_EXCL, 0600, 
        jf::POSIXMessageQueue::Attr().set_maxmsg(5).set_msgsize(sizeof(message_A)));
    jf::POSIXMessageQueue::create(
        queue_name_B, O_RDWR|O_EXCL, 0600, 
        jf::POSIXMessageQueue::Attr().set_maxmsg(5).set_msgsize(sizeof(message_B)));
    return 0;
}
