#include "test.h"
#include <stdint.h>

/*
 * Reproducer for 70-test_quic_multistream.t failure.
 * Checks for unsigned 64-bit comparison errors (signed vs unsigned).
 */
int main() {
    uint64_t a = 0x8000000000000000ULL;
    if (a < 100ULL) {
        printf("FAIL: 0x8000000000000000 < 100 is TRUE (likely treated as signed negative)\n");
        return 1;
    }
    printf("PASS\n");
    return 0;
}