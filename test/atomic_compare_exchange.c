#include <stdio.h>
#include <stdbool.h>
#include "test.h"
typedef struct pg_atomic_uint32 {
    volatile unsigned int value;
} pg_atomic_uint32;

static inline bool pg_atomic_compare_exchange_u32_impl(volatile pg_atomic_uint32 *ptr,
                                                       unsigned int *expected, unsigned int newval) {
    char ret;
    __asm__ __volatile__(
        "lock\n"
        "cmpxchgl %4,%5\n"
        "setz %2\n"
        : "=a" (*expected), "=m" (ptr->value), "=q" (ret)
        : "a" (*expected), "r" (newval), "m" (ptr->value)
        : "memory", "cc");
    return (bool) ret;
}

int main() {
    pg_atomic_uint32 val = {10};
    unsigned int expected = 10;
    bool result = pg_atomic_compare_exchange_u32_impl(&val, &expected, 20);
    printf("Compare and Exchange: %d, New Value: %u\n", result, val.value);
    Assert(1, result);
    Assert(20, val.value);
    return 0;
}
