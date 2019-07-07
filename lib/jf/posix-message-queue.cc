#include "posix-message-queue.h"

#include "system-error.h"

#include <cstring>
#include <cassert>


namespace jf {

POSIXMessageQueue::Attr::Attr()
{
    memset(this, 0, sizeof(*this));
}

POSIXMessageQueue POSIXMessageQueue::create_raw(
    const std::string& path, 
    int oflag, 
    mode_t mode, 
    const Attr& attr)
{
    oflag |= O_CREAT;

    mqd_t mq = mq_open(path.c_str(), oflag, mode, &attr);
    if (mq < 0)
        throw SystemError(errno, "mq_open(O_CREAT)");

    POSIXMessageQueue ret;
    ret.fd_ = FD(mq);
    return ret;
}

POSIXMessageQueue POSIXMessageQueue::open_raw(
    const std::string& path, 
    int oflag)
{
    assert(!(oflag&O_CREAT));
    
    mqd_t mq = mq_open(path.c_str(), oflag);
    if (mq < 0)
        throw SystemError(errno, "mq_open()");

    POSIXMessageQueue ret;
    ret.fd_ = FD(mq);
    return ret;
}

void POSIXMessageQueue::unlink(
    const std::string& path)
{
    if (mq_unlink(path.c_str()) < 0)
        throw SystemError(errno, "mq_unlink()");
}

void POSIXMessageQueue::send_raw(
    const void* msg, 
    size_t msg_len, 
    unsigned priority)
{
    if (mq_send(fd_, (const char*)msg, msg_len, priority) < 0)
        throw SystemError(errno, "mq_send()");
}

size_t POSIXMessageQueue::receive_raw(
    void* msg, 
    size_t msg_len)
{
    unsigned prio;
    ssize_t nread = mq_receive(fd_, (char*)msg, msg_len, &prio);
    if (nread < 0)
        throw SystemError(errno, "mq_receive()");
    return nread;
}

}
