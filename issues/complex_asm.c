#include "test.h"

int main() {
    int x = 5;
    int dst = 0;

    // Extended assembly with complex operand names
    __asm__ volatile (
        "add %1, %0\n"
        : [dst+2*x] "=r" (dst)     // output operand name
        : [src*3] "r" (x)          // input operand name
    );

    printf("dst = %d\n", dst);
    return 0;
}
