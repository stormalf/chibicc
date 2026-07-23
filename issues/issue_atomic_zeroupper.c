// Regression: __atomic_load_n for uint16_t must zero-extend its result.
// mov (%rax), %ax leaves upper bits of %eax dirty -> corruption in wider use.
#include "test.h"
#include <stdint.h>

uint16_t global_u16;

// Simulate what SQLite wal.c does: load uint16_t from hash table,
// then use it in pointer arithmetic or wider comparison.
uint16_t test_atomic_load_u16(void) {
    // Prior 32-bit operation that dirties upper bits of %eax
    volatile int noise = 0xDEADBEEF;
    (void)noise;
    return __atomic_load_n(&global_u16, __ATOMIC_SEQ_CST);
}

uint8_t global_u8;

uint8_t test_atomic_load_u8(void) {
    volatile int noise = 0xDEADBEEF;
    (void)noise;
    return __atomic_load_n(&global_u8, __ATOMIC_SEQ_CST);
}

int main() {
    global_u16 = 0xABCD;
    uint16_t v = test_atomic_load_u16();
    // If upper bits are garbage, (int)(uint32_t)v could be > 0xFFFF
    ASSERT(0xABCD, v);
    ASSERT(1, v <= 0xFFFF);

    global_u8 = 0x42;
    uint8_t b = test_atomic_load_u8();
    ASSERT(0x42, b);
    ASSERT(1, b <= 0xFF);

    // Test that result used in pointer arithmetic works
    int arr[256];
    int *p = arr + v;
    ASSERT((long)(p - arr), (long)v);

    printf("OK\n");
    return 0;
}
