#include <sched.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fork_return = fork();

    if (!fork_return) {
        // exit immediately from the child
        return 1;

        // child sends some singal to itself
        // kill(getpid(), 9);
    }

    char *parent_or_child = fork_return == 0 ? "Child" : "Parent";


    printf("continuing the %s\n", parent_or_child);

    int status;
    pid_t pid = wait(&status);

    if (pid == -1) perror("wait");

    printf("%s: pid = %d\n", parent_or_child, pid);

    if (WIFEXITED(status)) {
        printf("%s: Normal termination with exit status = %d\n", parent_or_child, WIFEXITED(status));
    }

    if (WIFSIGNALED(status)) {
        printf("%s: Killed by signal = %d %s \n", parent_or_child, WTERMSIG(status), WCOREDUMP(status) ? "(dumped core)" : "");
    }

    if (WIFSTOPPED(status)) {
        printf("%s: Stopped by signal = %d\n", parent_or_child, WSTOPSIG(status));
    }

    if (WIFCONTINUED(status)) {
        printf("%s: Continued", parent_or_child);
    }

    return 0;
}
