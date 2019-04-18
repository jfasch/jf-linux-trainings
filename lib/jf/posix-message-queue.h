#ifndef JF__POSIX_MESSAGE_QUEUE_H
#define JF__POSIX_MESSAGE_QUEUE_H

#include "fd.h"

#include <string>
#include <exception>
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
    struct BadSizeException : public std::exception
    {
        const char* what() const noexcept { return "bad message size"; }
    };

public:
    static POSIXMessageQueue create_raw(const std::string& path, int oflag, mode_t, const Attr&);
    static POSIXMessageQueue open_raw(const std::string& path, int oflag);
    static void unlink(const std::string& path);

    void send_raw(const void* msg, size_t msg_len, unsigned priority);
    size_t receive_raw(void* msg, size_t msg_len);

public:    
    template <typename MESSAGE>
    static POSIXMessageQueue create(const std::string& path, int oflag, mode_t mode, long maxmsg)
    {
        return create_raw(path, oflag, mode, Attr().set_maxmsg(maxmsg).set_msgsize(sizeof(MESSAGE)));
    }

    template <typename MESSAGE>
    static POSIXMessageQueue open(const std::string& path, int oflag)
    {
        return open_raw(path, oflag);
    }

    template <typename MESSAGE>
    void send(const MESSAGE& message, unsigned priority)
    {
        send_raw(&message, sizeof(message), priority);
    }

    template <typename MESSAGE>
    void receive(MESSAGE& message)
    {
        size_t nread = receive_raw(&message, sizeof(message));
        if (nread != sizeof(message)) throw BadSizeException();
    }

    const FD& fd() const { return fd_; }

private:
    FD fd_;
};

}

#endif
