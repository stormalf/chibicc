#include <stdio.h>
#include "test.h"
int main() {
    int count = __builtin_popcount(15); // 15 is 1111 in binary, so count is 4
    printf("Number of 1-bits: %d\n", count);
    ASSERT(4, count);
    return 0;
}

