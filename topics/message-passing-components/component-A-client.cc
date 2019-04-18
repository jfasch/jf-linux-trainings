#include "_protocols.h"

#include <jf/posix-message-queue.h>

#include <iostream>
#include <cstring>
#include <unistd.h>


int main()
{
    jf::POSIXMessageQueue q = 
        jf::POSIXMessageQueue::open<message_A>(queue_name_A, O_WRONLY);

    std::cout << "Asking component A to output \"hello!\"" << std::endl;
    {
        message_A message;
        message.request = message_A::request::SAYHELLO;
        strcpy(message.payload, "hello!");
        
        q.send(message, /*priority*/0);
    }

    sleep(1);
    
    std::cout << "Asking component A to ask component B to output \"hello!\"" << std::endl;
    {
        message_A message;
        message.request = message_A::request::SAYHELLO_DELEGATE_TO_B;
        strcpy(message.payload, "hello!");
        
        q.send(message, /*priority*/0);
    }
    
    return 0;
}
