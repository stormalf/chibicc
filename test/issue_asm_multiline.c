#include <stdio.h>
int main(void) {
    int a = 10, b = 0;
   asm ("movl %eax, %ebx\n\t" 
    "add  $10, %ebx\n\t"
    );

    printf("a=%d, b=%d\n", a, b);
    return 0;
}