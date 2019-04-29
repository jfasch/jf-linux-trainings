#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <cassert>
#include <iostream>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

    // open file
    int fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // trim size to hold a uint32_t
    int error = ftruncate(fd, sizeof(uint32_t));
    assert(!error);

    // map into memory, and initialize to 0
    void* mem = mmap(NULL, sizeof(uint32_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    assert(mem != MAP_FAILED);

    uint32_t* intptr = (uint32_t*)mem;

    while (true) {
        (*intptr)++;
        sleep(1);
    }

    return 0;
}
