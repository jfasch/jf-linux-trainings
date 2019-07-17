#include <jf/tcp4.h>

#include <iostream>
#include <cstdlib>


int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << argv[0] << " <ip> <port>" << std::endl;
        exit(1);
    }

    jf::TCP4Connection connection = jf::TCP4Connection(argv[1], std::stoi(argv[2]));

    const char payload[] = "hello\n";

    // send out payload.
    { 
        // write(2) does not guarantee that one write operation will
        // write all. So, to be exact, we have to use write() in a
        // loop until all is out on the socket. (it is unlikely but
        // still legally possible that "hello\n" does not make it onto
        // the air within one turn.)
        size_t nwritten = 0;
        while (nwritten != sizeof(payload))
            nwritten += connection.write(payload+nwritten, sizeof(payload)-nwritten);
    }

    // read until EOF what the server has to say, and echo to stdout.
    {
        char buf[64];
        size_t nread;
        while (true) {
            nread = connection.read(buf, sizeof(buf));
            if (nread == 0) // EOF
                break;
            std::cout.write(buf, nread);
        }
    }

    return 0;
}
