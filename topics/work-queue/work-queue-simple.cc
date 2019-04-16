#include <jf/work-queue.h>
#include <jf/tid.h>

#include <iostream>
#include <chrono>

#include <sys/syscall.h>


using namespace std::chrono_literals;


int main()
{
    jf::WorkQueue wq;
    auto work = []()
                {
                    std::this_thread::sleep_for(2s);
                    std::cout << "async work from TID " << jf::gettid() << std::endl;
                };
    std::cout << "enqueueing work in TID " << jf::gettid() << std::endl;
    wq.enqueue(work);
    std::cout << "waiting for termination" << std::endl;
    return 0;
}
