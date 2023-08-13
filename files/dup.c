#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int dup_fd = dup(0);

    if (dup_fd < 0) {
        perror("dup");
        return -1;
    }

    int new_stdin = open("newstdin.txt", O_RDWR);
    dup2(new_stdin, 0);

    char *num;

    scanf("%s", num);
    printf("thing from stdin: %s", num);

    return 0;
}
