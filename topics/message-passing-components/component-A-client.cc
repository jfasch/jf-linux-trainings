#include "_protocols.h"

#include <jf/posix-message-queue.h>

#include <cstring>


int main()
{
    jf::POSIXMessageQueue q = jf::POSIXMessageQueue::open(queue_name_A, O_WRONLY);

    message_A message;
    message.request = message_A::request::SAYHELLO_DELEGATE_TO_B;
    strcpy(message.payload, "hello!");

    q.send(&message, sizeof(message), /*priority*/0);
    
    return 0;
}
