#include "test.h"
#include <stdint.h>
#include <stdbool.h>

int main(void) {
    int x = 0;
    int y = 42;

    // Atomic store using __atomic_store_n
    __atomic_store_n(&x, y, __ATOMIC_SEQ_CST);

    // Atomic load using __atomic_load_n
    int z = __atomic_load_n(&x, __ATOMIC_SEQ_CST);

    printf("x = %d, y = %d, z = %d\n", x, y, z);
    ASSERT(42, x);
    ASSERT(42, y);
    ASSERT(42, z);
    // Modify x using store_n again
    __atomic_store_n(&x, 99, __ATOMIC_SEQ_CST);
    int w = __atomic_load_n(&x, __ATOMIC_SEQ_CST);

    printf("x = %d, w = %d\n", x, w);

    ASSERT(99, x);
    ASSERT(99, w);
    // Test with uint8_t
    uint8_t a = 5, b = 200;
    __atomic_store_n(&a, b, __ATOMIC_SEQ_CST);
    uint8_t c = __atomic_load_n(&a, __ATOMIC_SEQ_CST);

    printf("a = %u, b = %u, c = %u\n", a, b, c);

    ASSERT(200, a);
    ASSERT(200, b);
    ASSERT(200, c);
    return 0;
}
