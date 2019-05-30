#include "_protocols.h"

#include <jf/posix-message-queue.h>

#include <iostream>


int main()
{
    jf::POSIXMessageQueue::create<message_A>(queue_name_A, O_RDWR|O_EXCL, 0600, 5);
    jf::POSIXMessageQueue::create<message_B>(queue_name_B, O_RDWR|O_EXCL, 0600, 5);

    std::cerr << "Created POSIX message queues:\n";
    std::cerr << "  " << queue_name_A << '\n';
    std::cerr << "  " << queue_name_B << std::endl;

    return 0;
}
