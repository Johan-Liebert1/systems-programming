#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>

int main() {
    char greeting[] = "Hello there";
    char *c = &greeting[1];

    unsigned long not_good = *(unsigned long *)c;

    printf("c: %s, not_good: %lu\n", c, not_good);

    unsigned long long i = 1024l * 1024l * 1024l * 1024l;

    // getting anonymous memory
    void *p = mmap(
        NULL,
        i,
        PROT_READ | PROT_WRITE,
        MAP_ANONYMOUS | MAP_PRIVATE,
        -1,
        0
    );

    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    return 0;
}
