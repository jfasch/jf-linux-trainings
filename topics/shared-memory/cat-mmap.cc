#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <cassert>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // determine file size, mmap, and finally output
    off_t len = lseek(fd, 0, SEEK_END);
    void *mem = mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);
    ssize_t nwritten = write(STDOUT_FILENO, mem, len);
    assert(nwritten == len);
    return 0;
}
