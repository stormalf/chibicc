#include <stdio.h>
#include "test.h"
int main() {
    int result;

    if (__builtin_sub_overflow(-1, 1, &result)) {
        printf("Overflow detected!\n");
    }
    else {
        printf("Overflow not detected!\n");
    }
    ASSERT(0, __builtin_sub_overflow(-1, 1, &result));
    if (__builtin_sub_overflow(-2147483648, 1, &result)) {
        printf("Overflow detected!\n");
    }
    ASSERT(1, __builtin_sub_overflow(-2147483648, 1, &result));
    return 0;
}

