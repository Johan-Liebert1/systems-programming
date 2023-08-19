#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>

#define BUF_SIZE 200

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    char *filepath = argv[1];

    char *attrname = argc > 2 ? argv[2] : "user.my-new-xattr";

    printf("filepath: %s\n", filepath);

    char buf[BUF_SIZE];

    // this only lists all the keys
    int list_len = listxattr(filepath, buf, BUF_SIZE);

    if (list_len == -1) {
        printf("errno %d", errno);
        perror("listxattr");
        return 1;
    }

    printf("Buffer: %s. Listlen: %d\n", buf, list_len);

    char *value =  "this is the attr";
    int ret = setxattr(filepath, attrname, value, strlen(value), 0);

    if (ret == -1) {
        perror("setxattr");
        return 1;
    }

    listxattr(filepath, buf, BUF_SIZE);
    printf("Buffer: %s. Listlen: %d\n", buf, list_len);

    char attr_value[20];
    ret = getxattr(filepath, attrname, attr_value, 20);

    if (ret == -1) {
        perror("getxattr");
        return 1;
    }

    printf("\nFile: %s \nKey: %s \nValue: %s\n", filepath, attrname, attr_value);

}
