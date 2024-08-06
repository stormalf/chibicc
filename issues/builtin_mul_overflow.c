#include <stdio.h>
int main() {
    int result;
    if (__builtin_mul_overflow(2147483647, 2, &result)) {
        printf("Overflow detected!\n");
    }
    if (__builtin_mul_overflow(255, 2, &result)) {
        printf("Overflow detected!\n");
    } else
        printf("Overflow not detected!\n");
    return 0;
}

