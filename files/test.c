#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void naiive_read() {
    unsigned long word;
    ssize_t nr;

    int fd = open("hello.txt", O_RDONLY);

    nr = read(0, &word, sizeof (unsigned long));

    printf("%zd, %zd", nr, word);
}

void read_all_bytes() {
}

void write_things() {
    int fd = open("hello.txt", O_WRONLY);
    char *buf = "c";

    int ret = write(fd, buf, strlen(buf));
    ret = write(fd, buf, strlen(buf));

    printf("%d", ret);
}

int main() {
    write_things();
    return -1;
}
