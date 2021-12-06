#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// either thread can access global data
struct sum {
    long long limit;
    long long answer;
};

// thread function to generate sum of 0 to n
void* sum_runner(void* arg) {
    struct sum* arg_struct = (struct sum*)arg;
    long long limit = arg_struct->limit;

    arg_struct->answer = 0;

    for (long long i = 0; i <= limit; i++) {
        arg_struct->answer += i;
    }

    // send the answer back. Here 0 is the value we're sending back to the main thread
    pthread_exit(0);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <num 1> <num 2> ... <num n>\n", argv[0]);
        exit(1);
    }

    int num_args = argc - 1;

    // thread id
    pthread_t tids[num_args];

    // create attrs
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    struct sum args[num_args];

    for (int i = 0; i < num_args; i++) {
        args[i].limit = atoll(argv[i + 1]);

        pthread_create(&tids[i], &attr, sum_runner, &args[i]);
    }

    // don't wanna put this in the loop at it will join and wait for the thread to finish executing
    for (int i = 0; i < num_args; i++) {
        pthread_join(tids[i], NULL);
        printf("Sum of %lld is %lld. Thread id: %ld\n", args[i].limit, args[i].answer, tids[i]);
    }
}