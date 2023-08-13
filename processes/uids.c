#include <stdio.h>
#include <unistd.h>

int main() {
    int euid = geteuid();

    printf("euid before %d\n", euid);

    euid = setuid(0);

    if (euid < 0) {
        perror("euid");
        return 1;
    }
    
    printf("euid after change %d", euid);

    return 0;
}
