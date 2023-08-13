#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <sys/stat.h>

/*
* get_physical_block - for the file associated with the given fd; returns 
* the physics block mapping to logical blocks
*/
int get_physical_block(int fd, int logical_block) {
    int ret = ioctl(fd, FIBMAP, &logical_block);

    if (ret < 0) {
        perror("ioctl");
        return -1;
    }

    return logical_block;
}

/*
* get_nr_blocks - returns the number of logical blocks
* consumed by the file associated with fd
*/
int get_nr_blocks(int fd) {
    struct stat buf;
    int ret = fstat(fd, &buf);

    if (ret < 0) {
        perror("fstat");
        return -1;
    }

    return buf.st_blocks;
}


/*
* print_blocks - for each logical block consumed by the file associated with fd, prints
* to stdout the tuple (logical_block, physical_block)
*/
void print_blocks(int fd) {
    int nr_blocks = get_nr_blocks(fd);

    if (nr_blocks <= 0) {
        char *msg = nr_blocks < 0 ?   "get_nr_blocks failed\n" : "no allocated blocks\n";
        fprintf(stderr, "%s", msg);
        return;
    }


    printf("%d blocks\n\n", nr_blocks);


    for (int i = 0; i < nr_blocks; i++) {
        int physical_block = get_physical_block(fd, i);

        if (physical_block < 0) {
            fprintf(stderr, "get_block failed\n");
            return;
        }

        if (!physical_block) continue;

        printf("(%d, %d) ", i, physical_block);
    }

    putchar('\n');
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    print_blocks(fd);
    return 0;
}
