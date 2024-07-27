#include <stdio.h>
#include "test.h"
int add(int a, int b) {
    asm ("add %1, %0\n\t" 
        : "+r" (a)
        : "r" (b)
        : "cc"
    );
    return a;
}

int main(void) {
    int result = add(10, 21);
    printf("%d\n", result);
    ASSERT(31, result);
    return 0;
}
