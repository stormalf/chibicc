#include <stdio.h>
//#include <stdatomic.h>


static inline int __sync_lock_test_and_set(int *ptr, int value) {
    int old_value;
    __asm__ __volatile__(
        "xchgl %0, %1"
        : "=r" (old_value), "+m" (*ptr)
        : "0" (value)
        : "memory"
    );
    return old_value;
}

int main() {
    int value = 5;
    int old_value = __sync_val_compare_and_swap(&value, 5, 10);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 5, New value: 10
    return 0;
}

