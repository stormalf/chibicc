
#include "test.h"

int main(void) {
    int a = 10, b = 21;
   asm ("add %1, %0\n\t" 
    :  "+r" (a)
    : "r" (b)
    : "cc"
    );
    printf("%d\n", a);
    printf("%d\n", b);
    ASSERT(31, a);
    ASSERT(21, b);
    
    return 0;
}