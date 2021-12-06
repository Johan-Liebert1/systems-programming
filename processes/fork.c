#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    // char *args[4] = {"/bin/echo", "Hello, ", "World!", 0};

    // int child_status, result;

    // result = fork();

    int result = 1;

    printf("Result = %d", result);

    return 0;
}