#include <stdio.h>
#include <unistd.h>

int main() {
    int ret = execl("/bin/zsh", "zsh", NULL);

    if (ret < 1) {
        perror("execl");
    }

    return ret;
}
