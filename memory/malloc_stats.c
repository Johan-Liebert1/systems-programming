#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>

int main(int argc, char *argv[]) { 
    char *c = "hello";

    malloc(40);

    malloc_stats();

    // main(argc, argv);

    return EXIT_SUCCESS; 
}
