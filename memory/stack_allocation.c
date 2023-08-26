#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

int main(int argc, char *argv[]) {
    unsigned long i = 1024l * 1024 * 1024 * 1024;

    void *c = alloca(i);

    if (!c) {
        perror("alloca");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
