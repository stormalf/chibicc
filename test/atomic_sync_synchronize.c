
#include <pthread.h>
#include "test.h"

int shared_value = 0;

void *thread_func(void *arg) {
    __sync_synchronize(); // Memory barrier
    shared_value = 42;
    __sync_synchronize(); // Memory barrier
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
    printf("Shared value: %d\n", shared_value); // Shared value: 42
    ASSERT(42, shared_value);
    return 0;
}

