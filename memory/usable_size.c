#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    size_t len = 21;

    // is actually padded with 3 bytes to make it word aligned
    char *buf = malloc(len);

    if (!buf) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    
    size_t size = malloc_usable_size(buf);

    printf("usable size %zu\n", size);

    return EXIT_SUCCESS;
}
