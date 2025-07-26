#include "test.h"
#include <stdatomic.h>
#include <threads.h>

atomic_flag lock = ATOMIC_FLAG_INIT;
int counter = 0;

void spinlock_lock(atomic_flag *lock) {
    while (atomic_flag_test_and_set(lock)) {
        // busy wait
    }
}

void spinlock_unlock(atomic_flag *lock) {
    atomic_flag_clear(lock);
}

int thread_func(void *arg) {
    for (int i = 0; i < 100000; i++) {
        spinlock_lock(&lock);
        counter++;
        spinlock_unlock(&lock);
    }
    return 0;
}

int main() {
    thrd_t t1, t2;

    thrd_create(&t1, thread_func, NULL);
    thrd_create(&t2, thread_func, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    printf("Final counter value: %d (expected 200000)\n", counter);
    ASSERT(200000, counter);
    return 0;
}
