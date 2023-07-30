#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // will ignore the sigint signal
    signal(SIGINT, SIG_IGN);

    unsigned long int counter = 0;

    while (1) {
        printf("Counter is %lu\n", ++counter);
        usleep(500000);  // 500ms
    }

    return 0;
}
