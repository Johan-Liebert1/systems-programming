#define _GNU_SOURCE

#include <stdio.h>
#include <sched.h>

/* only allow process to be scheduled on some certain CPU */
void set_process_cpu_affinity() {
    cpu_set_t set;

    CPU_ZERO(&set); // clear all CPUs
    CPU_SET(0, &set); // allow only CPU #0, as we've cleared all other CPUs above
    
    printf("%lu\n", *set.__bits);

    // set the CPU affinity of the current process
    int ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);

    printf("%lu\n", *set.__bits);

    if (ret == -1) {
        perror("sched_setaffinity");
        return;
    }

    for (int i = 0; i < CPU_SETSIZE; i++) {
        int cpu = CPU_ISSET(i, &set);

        if (!cpu) continue;

        printf("cpu=%i is %s\n", i, cpu ? "set" : "unset");
    }
}

int no_of_cpus() {
    cpu_set_t set;

    CPU_ZERO(&set);

    printf("set %lu\n", *set.__bits);

    int ret = sched_getaffinity(0, sizeof(cpu_set_t), &set);

    printf("set %lu\n", *set.__bits);

    if (ret == -1) {
        perror("sched_getaffinity");
        return 1;
    }

    for (int i = 0; i < CPU_SETSIZE; i++) {
        int cpu = CPU_ISSET(i, &set);

        if (!cpu) continue;

        printf("cpu=%i is %s\n", i, cpu ? "set" : "unset");
    }

    return 0;
}

int main() {
set_process_cpu_affinity();
}
