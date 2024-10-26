#include <stdio.h>
#include "test.h"
static inline int __sync_bool_compare_and_swap(int *ptr, int oldval, int newval) {
    char result;
    __asm__ __volatile__(
        "lock; cmpxchgl %2, %1\n\t"
        "sete %0"
        : "=q" (result), "+m" (*ptr), "+a" (oldval)
        : "r" (newval)
        : "memory");
    return result;
}


int main() {
    int value = 5;
    int result = __sync_bool_compare_and_swap(&value, 5, 10);
    printf("Compare and swap result: %d, New value: %d\n", result, value); // Result: 1, value: 5
    ASSERT(1, result);
    ASSERT(5, value);
    return 0;
}

