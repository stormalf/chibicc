#include "test.h"
#include <stdint.h>

/*
 * Reproducer for 70-test_quic_radix.t failure.
 * Focuses on 64-bit bitwise operations and builtins used by OpenSSL's QUIC_RATREE.
 */
int main() {
    uint64_t key = 0x8000000000000000ULL;
    int leading_zeros = __builtin_clzll(key);
    
    if (leading_zeros != 0) {
        printf("FAIL: __builtin_clzll(0x8000000000000000) = %d (expected 0)\n", leading_zeros);
        return 1;
    }

    uint64_t val = 1ULL << 35;
    if (val == 0) {
        printf("FAIL: 1ULL << 35 resulted in 0 (promotion or shift width issue)\n");
        return 1;
    }

    printf("PASS\n");
    return 0;
}