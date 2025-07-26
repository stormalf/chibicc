#ifdef __x86_64__

#include <stdbool.h>
#include "test.h"

typedef struct pg_atomic_uint64 {
    volatile unsigned long long value;
} pg_atomic_uint64;

static inline bool pg_atomic_compare_exchange_u64_impl(volatile pg_atomic_uint64 *ptr,
                                                       unsigned long long *expected, unsigned long long newval) {
    char ret;
    __asm__ __volatile__(
        "lock\n"
        "cmpxchgq %4,%5\n"
        "setz %2\n"
        : "=a" (*expected), "=m" (ptr->value), "=q" (ret)
        : "a" (*expected), "r" (newval), "m" (ptr->value)
        : "memory", "cc");
    return (bool) ret;
}

int main() {
    pg_atomic_uint64 val = {10};
    unsigned long long expected = 10;
    bool result = pg_atomic_compare_exchange_u64_impl(&val, &expected, 20);
    printf("Compare and Exchange U64: %d, New Value: %llu\n", result, val.value);
    ASSERT(1, result);
    ASSERT(20, val.value);
    return 0;
}
#endif
