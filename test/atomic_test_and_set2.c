
#include <stdbool.h>
#include "test.h"

typedef struct pg_atomic_flag {
    volatile char value;
} pg_atomic_flag;

static inline bool pg_atomic_test_set_flag_impl(volatile pg_atomic_flag *ptr) {
    char _res = 1;
    __asm__ __volatile__(
        "lock\n"
        "xchgb %0,%1\n"
        : "+q" (_res), "+m" (ptr->value)
        :
        : "memory");
    return _res == 0;
}

int main() {
    pg_atomic_flag flag = {0};
    bool result = pg_atomic_test_set_flag_impl(&flag);
    printf("Test and Set Flag: %d\n", result);
    ASSERT(1, result);
    return 0;
}
