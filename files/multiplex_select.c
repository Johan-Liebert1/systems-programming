#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define TIMEOUT 5
#define BUF_LEN 1024

int main() {
    struct timeval tv;
    fd_set readfs;
    int ret;

    // wait on stdin for input
    FD_ZERO(&readfs); // FD_ZERO removes all fds from the specified set

    // FD_SET adds a file descriptor to a given set
    FD_SET(STDIN_FILENO, &readfs);

    // wait for TIMEOUT seconds
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;

    // now we block
    ret = select(STDIN_FILENO + 1, &readfs, NULL, NULL, &tv);

    if (ret == -1) {
        perror("select");
        return 1;
    } else if (!ret) {
        printf("%d seconds elapsed.\n", TIMEOUT);
        return 0;
    }

    // is our file descriptor ready to read.
    // this is redundant here as it was the only fd provided to select
    if (FD_ISSET(STDIN_FILENO, &readfs)) {
        char buf[BUF_LEN + 1];
        int len;

        // guaranteed to not block
        len = read(STDIN_FILENO, buf, BUF_LEN);

        if (len == -1) {
            perror("read");
            return 1;
        }

        if (len) {
            buf[len] = '\0';
            printf("read: %s\n", buf);
        }

        return 0;
    }

    fprintf(stderr, "this should not have happened\n");
    return 1;
}
