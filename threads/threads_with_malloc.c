#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

// thread function to generate sum of 0 to n
void* sum_runner(void* arg) {
    ll* limit_ptr = (ll*)arg;
    ll limit = *limit_ptr;

    free(arg);

    ll sum = 0;

    for (ll i = 0; i <= limit; i++) {
        sum += i;
    }

    // pass back data in dynamically allocated mem
    ll* answer = malloc(sizeof(*answer));

    *answer = sum;

    pthread_exit(answer);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s list[num]\n", argv[0]);
        exit(-1);
    }

    ll* limit = malloc(sizeof(limit));

    *limit = atoll(argv[1]);

    // thread id
    pthread_t tid;

    // create attrs
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_create(&tid, &attr, sum_runner, limit);

    ll* result;

    // wait until thread has done its work
    pthread_join(tid, (void**)&result);

    printf("Sum is %lld\n", *result);
    free(result);
}