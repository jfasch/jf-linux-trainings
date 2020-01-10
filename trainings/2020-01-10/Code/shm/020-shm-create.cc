#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    int fd = shm_open("mein-shared-dings", O_CREAT|O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    int error = ftruncate(fd, 4096);
    if (error) {
        perror("ftruncate");
        return 1;
    }

    // off_t off = lseek(fd, 4095, SEEK_SET);
    // if (off == -1) {
    //     perror("lseek");
    //     return 1;
    // }
    // char c = 0;
    // ssize_t nwritten = write(fd, &c, 1);
    // if (nwritten == -1) {
    //     perror("write");
    //     return 1;
    // }

    return 0;
}
