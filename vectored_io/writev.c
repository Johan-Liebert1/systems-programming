#include <bits/types/struct_iovec.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>

#define VEC_SIZE 3

int main() { 
    struct iovec iov[VEC_SIZE];
    ssize_t nr;
    int fd, i;

    char *buf[] = {
        "This is the first line of the buffer 1\n",
        "This is the second line of the buffer 2\n",
        "This is the third line of the buffer 3\n"
    };

    fd = open("test_files/vec_io.txt", O_CREAT | O_TRUNC | O_WRONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // fill out the three iovec structres
    for (i = 0; i < VEC_SIZE; i ++) {
        iov[i].iov_base = buf[i];
        iov[i].iov_len = strlen(buf[i]) + 1;
    }

    // write out all buffers with a single call
    nr = writev(fd, iov, VEC_SIZE);

    if (nr == -1) {
        perror("writev");
        return 1;
    }

    printf("Wrote %zd bytes\n", nr);

    if (close(fd)) {
        perror("Close");
        return 1;
    }

    return 0;
}

