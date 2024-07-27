

#include <stdio.h>
#include "test.h"
int main() {

    int src = 1;
    int dst;

    asm ("mov %1, %0\n\t"
        "add $1, %0"
        : "=r" (dst)
        : "r" (src));

    printf("%d\n", dst);
    printf("%d\n", src);
    ASSERT(2, dst);
    ASSERT(1, src);
    return 0;
}