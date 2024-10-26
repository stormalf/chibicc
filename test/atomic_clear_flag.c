#include <stdio.h>
#include "test.h"

typedef struct pg_atomic_flag {
    volatile char value;
} pg_atomic_flag;

static inline void pg_atomic_clear_flag_impl(volatile pg_atomic_flag *ptr) {
    __asm__ __volatile__("" ::: "memory");
    ptr->value = 0;
}

int main() {
    pg_atomic_flag flag = {1};
    pg_atomic_clear_flag_impl(&flag);
    printf("Flag cleared: %d\n", flag.value);
    Assert(0, flag.value);
    return 0;
}
