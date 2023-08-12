#include <stdio.h>
#include <unistd.h>
#include <sys/user.h>

int main() {
    long page_size = sysconf(_SC_PAGESIZE);
    long page_size_from_get_page_size = getpagesize();

    long page_size_from_macro = PAGE_SIZE;

    printf(
        "page_size: %ld, page_size_from_get_page_size: %ld, page_size_from_macro %ld\n", 
        page_size, page_size_from_get_page_size, page_size_from_macro
    );

    return 0;
}
