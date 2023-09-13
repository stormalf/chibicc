#include <stdio.h>
#include "../test/test.h"
int main() {
    int a = 0;
    //printf("a = %d\n", a);
    int b;
    b = a;
    ASSERT(0, a);
    ASSERT(0, b);
    __asm__ ( "movl $10, %eax;"
                "movl $20, %ebx;"
                "addl %ebx, %eax;"
    );

    __asm__ ("movl %eax, %0;" : "=r" ( a ));
    //printf("a = %d\n", a);
    b = a;
    ASSERT(30, a);
    ASSERT(30, b);
    //test/assign1.exe
    // a = 0
    // a => 30 expected but got 21948
    // make: *** [Makefile:29: test] Error 1
}
