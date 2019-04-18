#include "_protocols.h"

#include <jf/posix-message-queue.h>


int main()
{
    jf::POSIXMessageQueue::unlink(queue_name_A);
    jf::POSIXMessageQueue::unlink(queue_name_B);
    return 0;
}
