

#include <stdio.h>
#include "test.h"

int main() {
    /* Add 10 and 20 and store result into register %eax */
    int eax=0;
    __asm__ ( "movl $10, %eax;"
                "movl $20, %ebx;"
                "addl %ebx, %eax;"
    );

    __asm__ ("movl %%eax, %0;" : "=r" ( eax ));
    int a;
    a = eax;
    printf("a = %d\n", a);
    ASSERT(30, eax);
   ASSERT(30, a);
    

    /* Subtract 20 from 10 and store result into register %eax */
    __asm__ ( "movl $10, %eax;"
                    "movl $20, %ebx;"
                    "subl %ebx, %eax;"
    );
    __asm__ ("movl %%eax, %0;" : "=r" ( eax ));
    ASSERT(-10, eax);
    printf("eax = %d\n", eax);
    

    /* Multiply 10 and 20 and store result into register %eax */
    __asm__ ( "movl $10, %eax;"
                    "movl $20, %ebx;"
                    "imull %ebx, %eax;"
    );
    __asm__ ("movl %%eax, %0;" : "=r" ( eax ));
    ASSERT(200, eax);
    printf("eax = %d\n", eax);
    
    return 0 ;
}