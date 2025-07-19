#include "test.h"

int main() {
    /* Add 10 and 20 and store result into register %eax */
    int teax=0, tebx = 0, tecx = 0;
    __asm__ ( "movl $10, %eax;"
                "movl $20, %ebx;"
                "addl %ebx, %eax;"
    );

    __asm__ ("movl %%eax, %0;" : "=r" ( teax ));
    ASSERT(30, teax);
    printf("eax = %d\n", teax);
    
    /* Subtract 20 from 10 and store result into register %eax */
    __asm__ ( "movl $10, %eax;"
                    "movl $20, %ebx;"
                    "subl %ebx, %eax;"
    );
    __asm__ ("movl %%eax, %0;" : "=r" ( teax ));
    ASSERT(-10, teax);
    printf("eax = %d\n", teax);
    

    /* Multiply 10 and 20 and store result into register %eax */
    __asm__ ( "movl $10, %eax;"
                    "movl $20, %ebx;"
                    "imull %ebx, %eax;"
    );
    __asm__ ("movl %%eax, %0;" : "=r" ( teax ));
    ASSERT(200, teax);
    printf("eax = %d\n", teax);
    
    return 0 ;
}