#include <pthread.h>
#include <stdio.h>

typedef long long loong;

#define NUM_LOOPS 50000000

loong sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* counting_function(void* arg) {
    int offset = *(int*)arg;

    for (int i = 0; i < NUM_LOOPS; i++) {
        // start mutext
        pthread_mutex_lock(&mutex);  // syscall

        sum += offset;

        // end mutex
        pthread_mutex_unlock(&mutex);  // syscall
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t id1, id2;

    int offset1 = 1, offset2 = -1;

    pthread_create(&id1, NULL, counting_function, &offset1);

    pthread_create(&id2, NULL, counting_function, &offset2);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("Sum = %lld\n", sum);

    return 0;
}