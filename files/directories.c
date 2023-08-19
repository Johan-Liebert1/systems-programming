#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <dir_name>\n", argv[0]);
        return 1;
    }

    char *dirpath = argv[1];
    DIR *dir = opendir(dirpath);

    struct dirent *dir_entry;

    // readdir returns NULL at the end of the directory stream and on error
    errno = 0;
    while ((dir_entry = readdir(dir)) != NULL) {
        printf("File(type = %d): %s\n", dir_entry->d_type, dir_entry->d_name);
    }

    closedir(dir);

    if (errno && !dir_entry) {
        perror("readdir");
        return 1;
    }

    return 0;
}
