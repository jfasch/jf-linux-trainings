#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cassert>
#include <iostream>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

    // open file
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // map into memory
    void* mem = mmap(NULL, sizeof(uint32_t), PROT_READ, MAP_SHARED, fd, 0);
    assert(mem != MAP_FAILED);
    uint32_t* intptr = (uint32_t*)mem;

    while (true) {
        std::cout << *intptr << std::endl;
        sleep(1);
    }

    return 0;
}
