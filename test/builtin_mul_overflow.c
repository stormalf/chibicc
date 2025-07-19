
#include "test.h"
int main() {
    int result;
    if (__builtin_mul_overflow(2147483647, 2, &result)) {
        printf("Overflow detected!\n");
    }
    ASSERT(1, __builtin_mul_overflow(2147483647, 2, &result));
    if (__builtin_mul_overflow(55, 2, &result)) {
        printf("Overflow detected!\n");
    } else
        printf("Overflow not detected!\n");
    ASSERT(0, __builtin_mul_overflow(55, 2, &result));
    return 0;
}

