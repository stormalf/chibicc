#include <stdio.h>
#include "test.h"
typedef struct pg_atomic_uint32 {
    volatile unsigned int value;
} pg_atomic_uint32;

static inline unsigned int pg_atomic_fetch_add_u32_impl(volatile pg_atomic_uint32 *ptr, int add_) {
    unsigned int res;
    __asm__ __volatile__(
        "lock\n"
        "xaddl %0,%1\n"
        : "=q"(res), "=m"(ptr->value)
        : "0" (add_), "m"(ptr->value)
        : "memory", "cc");
    return res;
}

int main() {
    pg_atomic_uint32 val = {10};
    unsigned int old_val = pg_atomic_fetch_add_u32_impl(&val, 5);
    printf("Fetch and Add: Old Value: %u, New Value: %u\n", old_val, val.value);
    Assert(10, old_val);
    Assert(15, val.value);
    return 0;
}
