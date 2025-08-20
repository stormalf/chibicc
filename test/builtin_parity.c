#include "test.h"

int main(void) {
    // Immediate constant
    int p1 = __builtin_parity(0x12345678);
    printf("parity(0x12345678) = %d\n", p1);

    // Variable / runtime value
    unsigned int x = 0xDEADBEEF;
    int p2 = __builtin_parity(x);
    printf("parity(0xDEADBEEF) = %d\n", p2);

    // Another constant
    int p3 = __builtin_parity(0xFFFFFFFF);
    printf("parity(0xFFFFFFFF) = %d\n", p3);

    ASSERT(1, p1);
    ASSERT(0, p2);
    ASSERT(0, p3);

    return 0;
}
