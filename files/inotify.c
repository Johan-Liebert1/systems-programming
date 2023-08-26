#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>

int main() {
    int fd = inotify_init();

    if (fd == -1) {
        perror("inotify_init");
        return 1;
    }

    int wd = inotify_add_watch(fd, "/home/pragyan/systems-programming", IN_ACCESS | IN_MODIFY | IN_CREATE);

    if (wd == -1) {
        perror("inotify_add_watch");
        return 1;
    }

    // reading the events
    char buf[256] __attribute__((aligned(4)));

    // read 256 bytes' worth of events
    ssize_t len = read(fd, buf, 256);

    ssize_t i = 0;

    while (i < len) {
        struct inotify_event *event = (struct inotify_event *)&buf;

        printf("wd=%d mask=%d cookie=%d len=%d dir=%s\n", event->wd,
               event->mask, event->cookie, event->len,
               (event->mask & IN_ISDIR) ? "yes" : "no");

        if (event->len) {
            printf("name=%s\n", event->name);
        }

        // update the index to the start of the next event
        i += sizeof (struct inotify_event) + event->len;
        len = read(fd, buf, 256);

        printf("i=%zd, len=%zd\n", i, len);
    }
}
