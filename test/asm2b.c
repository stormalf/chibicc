#include <stdio.h>
#include "test.h"

void someasm(void) {

    /* Add 10 and 20 and store result into register %eax */
    int eax=0, ebx = 0;
    __asm__ ( "movl $10, %eax;"
                "movl $20, %ebx;"
                "addl %ebx, %eax;"
    );

    __asm__ ("movl %%eax, %0;" : "=r" ( eax ));
    printf("eax = %d\n", eax);
     
    ASSERT(30, eax);    

    /* Subtract 20 from 10 and store result into register %eax */
    __asm__ ( "movl $10, %eax;"
                    "movl $20, %ebx;"
                    "subl %ebx, %eax;"
    );
    __asm__ ("movl %%eax, %0;" : "=r" ( eax ));
    printf("eax = %d\n", eax);
    
    ASSERT(-10, eax);
    

    /* Multiply 10 and 20 and store result into register %eax */
    __asm__ ( "movl $10, %eax;"
                    "movl $20, %ebx;"
                    "imull %ebx, %eax;"
    );
    __asm__ ("movl %%eax, %0;" : "=r" ( eax ));
    printf("eax = %d\n", eax);
    
    ASSERT(200, eax); 

}

int main() {

    someasm();
    
    return 0 ;
}