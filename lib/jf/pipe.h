#ifndef JF__PIPE_H
#define JF__PIPE_H

#include "fd.h"


namespace jf {

class Pipe
{
public:
    Pipe();

    FD& reader() { return reader_; }
    FD& writer() { return writer_; }

    void close_reader() { reader_.close(); }
    void close_writer() { writer_.close(); }

private:
    FD reader_;
    FD writer_;
};

}

#endif
