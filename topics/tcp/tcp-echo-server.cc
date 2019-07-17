#include <jf/tcp4.h>

#include <iostream>
#include <cstdlib>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << argv[0] << " <port>" << std::endl;
        exit(1);
    }

    jf::TCP4Port port(std::stoi(argv[1]));

    // accept connections, iteratively. this is, there is no
    // parallelism going on - one connection is accepted only if we
    // see EOF on the previous.
    while (true) {
        jf::TCP4Connection connection = port.accept();

        // echo incoming bytes until EOF.
        while (true) {
            char bytes[64];
            size_t nread = connection.read(bytes, sizeof(bytes));
            if (nread == 0) // EOF
                break;

            // write(2) does not guarantee that one write operation
            // will write all. So, to be exact, we have to use write()
            // in a loop until all is out on the socket.
            size_t nwritten = 0;
            while (nwritten != nread)
                nwritten += connection.write(bytes+nwritten, nread-nwritten);
        }
    }

    return 0;
}
