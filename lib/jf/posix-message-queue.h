#ifndef JF__POSIX_MESSAGE_QUEUE_H
#define JF__POSIX_MESSAGE_QUEUE_H

#include "fd.h"

#include <string>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

namespace jf {

class POSIXMessageQueue
{
public:
    struct Attr : public mq_attr
    {
        Attr();
        Attr& set_maxmsg(long l) { mq_maxmsg = l; return *this; }
        Attr& set_msgsize(long l) { mq_msgsize = l; return *this; }
    };

    static POSIXMessageQueue create(const std::string& path, int oflag, mode_t, const Attr&);
    static POSIXMessageQueue open(const std::string& path, int oflag);
    static void unlink(const std::string& path);

public:
    void send(const char* msg, size_t msg_len, unsigned priority);
    size_t receive(char* msg, size_t msg_len);

private:
    FD fd_;
};

}

#endif
