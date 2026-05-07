#include <stdio.h>

/*
 * Reproducer for OpenSSL 25-test_req.t Test 80 failure.
 * This test demonstrates a bug in chibicc's extended assembly
 * when frame pointer omission is enabled (-O1 or higher).
 * chibicc hardcodes (%rbp) for "m" constraints even when rbp is not used.
 */

void __attribute__((noinline)) test_asm_m(int x) {
    int val = x;
    int result = 0;
    /* In an optimized build, chibicc will use (%rbp) here but won't setup rbp */
    asm("mov %1, %0" : "=r"(result) : "m"(val));
    
    if (result != x) {
        printf("FAIL: result=%d (expected %d). Likely used wrong base register for 'm' constraint.\n", result, x);
    } else {
        printf("PASS\n");
    }
}

int main() {
    test_asm_m(42);
    return 0;
}