#include <stdio.h>
#include "test.h"
int main() {
    int trailing_zeros = __builtin_ctz(16); // 16 is 10000 in binary, so trailing_zeros is 4
    printf("Trailing zeros: %d\n", trailing_zeros);
    ASSERT(4, trailing_zeros);
    return 0;
}

