#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MESSAGE "You can't stop me\n"
#define MSG_LEN 19

static void signal_handler(int signal) {
    if (signal == SIGINT) {
        write(STDOUT_FILENO, MESSAGE, MSG_LEN);
    }
}

int main() {
    unsigned long int counter = 0;

    signal(SIGINT, signal_handler);

    while (1) {
        printf("Counter is %d\n", ++counter);
        usleep(500000);  // 500ms
    }

    return 0;
}