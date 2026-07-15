#include "test.h"
#include <stdint.h>

// Shifting a value by >= its width is undefined behavior in C, and each
// compiler (chibicc/gcc/clang) is free to produce a different result.
// OpenSSL guards such shifts explicitly; do the same so the behavior is
// well-defined on every compiler. Use a volatile count to prevent the
// compiler from constant-folding the shift away.
static uint64_t shl_u64(uint64_t x, unsigned n) {
    return (n >= 64) ? 0 : (x << n);
}

int main() {
    volatile unsigned n = 64;
    uint64_t x = 1;

    uint64_t y = shl_u64(x, n);

    if (y != 0) {
        printf("FAIL: %lx\n", y);
        return 1;
    }

    printf("OK\n");
}
