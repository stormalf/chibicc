#ifdef __x86_64__
#include <stdio.h>
#include "test.h"
typedef struct pg_atomic_uint64 {
    volatile unsigned long long value;
} pg_atomic_uint64;

static inline unsigned long long pg_atomic_fetch_add_u64_impl(volatile pg_atomic_uint64 *ptr, long long add_) {
    unsigned long long res;
    __asm__ __volatile__(
        "lock\n"
        "xaddq %0,%1\n"
        : "=q"(res), "=m"(ptr->value)
        : "0" (add_), "m"(ptr->value)
        : "memory", "cc");
    return res;
}

int main() {
    pg_atomic_uint64 val = {10};
    unsigned long long old_val = pg_atomic_fetch_add_u64_impl(&val, 5);
    printf("Fetch and Add U64: Old Value: %llu, New Value: %llu\n", old_val, val.value);
    ASSERT(10, old_val);
    ASSERT(15, val.value);
    return 0;
}
#endif
