#include <fcntl.h>
#include <stdio.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int cwd = open(".", O_RDONLY | O_DIRECTORY);
    printf("cwd: %d\n", cwd);

    if (cwd < 0) {
        perror("open");
        return cwd;
    }

    int fsopen_ret = fsopen("erofs", 0);
    printf("fsopen_ret: %d\n", fsopen_ret);

    if (fsopen_ret < 0) {
        perror("fsopen");
        return fsopen_ret;
    }

    char *erofs_path = "/home/pragyan/RedHat/composefs-rs/examples/bls/tmp/sysroot/composefs/images/"
                       "516d641a4b347ed2335bb191f9c43050478535b7e11d0985f1b88efcd0316320";

    // open an erofs image
    int erofs_image = open(erofs_path, O_RDONLY);

    if (erofs_image < 0) {
        perror("open erofs_image");
        return erofs_image;
    }

    int fsconfig_ret;

    fsconfig_ret = fsconfig(fsopen_ret, FSCONFIG_SET_FLAG, "ro", NULL, 0);
    if (fsconfig_ret < 0) {
        perror("first fsconfig");
        return fsconfig_ret;
    }

    char buf[1024];
    sprintf(buf, "/proc/self/fd/%d", erofs_image);

    fsconfig_ret = fsconfig(fsopen_ret, FSCONFIG_SET_STRING, "source", buf, 0);
    if (fsconfig_ret < 0) {
        perror("second fsconfig");
        return fsconfig_ret;
    }

    fsconfig(fsopen_ret, FSCONFIG_CMD_CREATE, NULL, NULL, 0);
    if (fsconfig_ret < 0) {
        perror("third fsconfig");
        return fsconfig_ret;
    }

    int fsmount_ret = fsmount(fsopen_ret, 0, 0);
    printf("fsmount_ret: %d\n", fsmount_ret);

    if (fsmount_ret < 0) {
        perror("fsmount");
        return fsmount_ret;
    }

    sleep(1000);

    int move_mount(int from_dfd, const char *from_pathname, int to_dfd, const char *to_pathname, unsigned int flags);

    return 0;
}

// int move_mount(int from_dirfd, const char *from_pathname,
//  int to_dirfd, const char *to_pathname,
//  unsigned int flags);
