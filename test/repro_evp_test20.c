#include "test.h"
#include <stdint.h>

/*
 * Reproducer for 30-test_evp.t test 20 failure.
 * Exercises __int128 multiplication critical for X25519/Ed25519.
 */
int main() {
    uint64_t a = 0xFFFFFFFFFFFFFFFFULL;
    uint64_t b = 0xFFFFFFFFFFFFFFFFULL;
    unsigned __int128 res = (unsigned __int128)a * b;
    
    uint64_t high = (uint64_t)(res >> 64);
    uint64_t low = (uint64_t)res;
    
    /* (2^64-1)^2 = 2^128 - 2^65 + 1 => high: 2^64-2, low: 1 */
    if (high != 0xFFFFFFFFFFFFFFFEULL || low != 0x0000000000000001ULL) {
        printf("FAIL: __int128 multiplication error: got %lx %lx\n", high, low);
        return 1;
    }
    
    printf("PASS\n");
    return 0;
}