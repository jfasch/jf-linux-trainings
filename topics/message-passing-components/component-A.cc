#include "_protocols.h"

#include <jf/posix-message-queue.h>
#include <jf/eventloop-epoll.h>
#include <jf/graceful-termination.h>

#include <iostream>
#include <cassert>
#include <cstring>


int main()
{
    try {
        jf::EventLoop_epoll loop;

        // add termination event handling to loop
        jf::GracefulTermination graceful_termination({SIGTERM, SIGINT});
        loop.watch_in(graceful_termination.fd(),
                      [&graceful_termination](int,jf::EventLoop*)
                      {
                          graceful_termination.make_request();
                      });

        // add message queue to loop
        jf::POSIXMessageQueue message_queue = jf::POSIXMessageQueue::open<message_A>(queue_name_A, O_RDONLY);        
        loop.watch_in(message_queue.fd(),
                      [&message_queue](int,jf::EventLoop*)
                      {
                          message_A message;
                          message_queue.receive(message);

                          switch (message.request) {
                              case message_A::request::SAYHELLO:
                                  std::cout << message.payload << std::endl;
                                  break;
                              case message_A::request::SAYHELLO_DELEGATE_TO_B:
                                  // delegate to component B
                                  jf::POSIXMessageQueue b_q = jf::POSIXMessageQueue::open<message_B>(queue_name_B, O_WRONLY);
                                  message_B message_b;
                                  message_b.request = message_B::request::SAYHELLO;
                                  strcpy(message_b.payload, message.payload);
                                  b_q.send(message_b, /*priority*/0);
                                  break;
                          }
                      });

        // run
        while (! graceful_termination.requested())
            loop.run_one();
        std::cerr << "Shutdown ..." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
}
