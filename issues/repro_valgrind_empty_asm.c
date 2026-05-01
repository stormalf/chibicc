#include <stdio.h>
#include <stdint.h>

// This mimics OpenSSL's value_barrier pattern.
// In chibicc 1.0.24, an empty template string causes the compiler 
// to skip operand processing, leaving 'r' uninitialized.
static inline uint32_t value_barrier_32(uint32_t a)
{
    uint32_t r;
    __asm__("" : "=r"(r) : "0"(a));
    return r;
}

int main(void)
{
    uint32_t x = 0x12345678;
    uint32_t y = value_barrier_32(x);

    // This conditional jump triggers the valgrind error if 'y' is uninitialized.
    if (y != x) {
        printf("Fail: %08x != %08x (Value was not preserved)\n", y, x);
        return 1;
    }

    printf("OK\n");
    return 0;
}