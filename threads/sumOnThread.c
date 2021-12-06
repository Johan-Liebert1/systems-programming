#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// either thread can access global data
long long sum = 0;

// thread function to generate sum of 0 to n
void* sum_runner(void* arg) {
    long long* limit_ptr = (long long*)arg;
    long long limit = *limit_ptr;

    for (long long i = 0; i <= limit; i++) {
        sum += i;
    }

    // send the answer back. Here 0 is the value we're sending back to the main thread
    pthread_exit(0);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s list[num]", argv[0]);
        exit(-1);
    }

    long long limit = atoll(argv[1]);

    // thread id
    pthread_t tid;

    // create attrs
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, sum_runner, &limit);

    // wait until thread has done its work
    pthread_join(tid, NULL);

    printf("Sum is %lld\n", sum);
}