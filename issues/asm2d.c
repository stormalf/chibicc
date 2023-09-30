
#include <stdio.h>
//#include "test.h"
int main() {
int src = 1;
int dst = 0;

__asm__ ("mov %1, %0\n\t"
    "add $1, %0"
    : "=r" (dst)
    : "r" (src));

printf("%d\n", dst);
printf("%ld %ld\n", sizeof(src), sizeof(dst));
//ASSERT(2, dst);
    return 0 ;
}