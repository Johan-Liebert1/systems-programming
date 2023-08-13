#include <linux/limits.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
* A process that daemonises itself
*/

int main() {
    // create a new process which will eventually be the daemon
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }

    // exit from parent
    if (pid != 0) exit(EXIT_SUCCESS);

    // create a new session and process group and set this process as leader
    // makes sure that the process has no associated controlling terminal
    if (setsid() == -1) {
        perror("setsid");
        return -1;
    }

    // set workdir to root dir so that daemon is not affected by mounting and 
    // unmounting of it's current working directory
    if (chdir("/") == -1) {
        perror("chdir");
        return -1;
    }

    // close all open files that the child inherited from parent
    // NR_OPEN is overkill but eh...
    for (int i = 0; i < NR_OPEN; i++) {
        close(i);
    }

    // redirect stdin, stdout, stderr to /dev/null
    open("/dev/null", O_RDWR);
    dup(0);
    dup(0);

    // daemon stuff
    
    return 0;
}
