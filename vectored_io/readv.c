#include <bits/types/struct_iovec.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/uio.h>
int main() {
    // the lengths of buffer also take into account the '\n' and the '\0'
    char first[40], second[41], third[40];
    
    struct iovec iov[3] = {
        { .iov_base =  first, .iov_len = sizeof(first) },
        {  .iov_base =  second, .iov_len = sizeof(second)  },
        {  .iov_base =  third, .iov_len = sizeof(third)  }
    };

    int fd = open("test_files/vec_io.txt", O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t nr = readv(fd, iov, 3);

    printf("Read %zd bytes\n", nr);

    printf("First: %s\n", first);
    printf("Second: %s\n", second);
    printf("Third: %s\n", third);
}
