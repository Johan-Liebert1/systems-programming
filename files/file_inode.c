#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int get_inode(int fd) {
    struct stat buf;

    int ret = fstat(fd, &buf);

    if (ret < 0) {
        perror("fstat");
        return -1;
    }

    return buf.st_ino;
}

int main() {
    char *file_name = "pages.c";

    int fd = open(file_name, O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("Inode for file %s is %d\n", file_name, get_inode(fd));
    
    return 0;
}
