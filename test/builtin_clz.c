
#include "test.h"
int main() {
    int leading_zeros = __builtin_clz(8); // 8 is 1000 in binary, so leading_zeros is 28 on a 32-bit system
    printf("Leading zeros: %d\n", leading_zeros);
    ASSERT(28, leading_zeros);
    return 0;
}

