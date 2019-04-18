#include "_protocols.h"

#include <jf/posix-message-queue.h>


int main()
{
    jf::POSIXMessageQueue::create<message_A>(queue_name_A, O_RDWR|O_EXCL, 0600, 5);
    jf::POSIXMessageQueue::create<message_B>(queue_name_B, O_RDWR|O_EXCL, 0600, 5);
    return 0;
}
