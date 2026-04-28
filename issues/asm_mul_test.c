// asm_array_min_test.c
#include <stdio.h>
#include <stdint.h>

typedef unsigned long BN_ULONG;

static BN_ULONG mul_high(BN_ULONG *ap, BN_ULONG w) {
    BN_ULONG high, low, carry = 0;

    asm("mulq %3"
        : "=a"(low), "=d"(high)
        : "a"(w), "m"(ap[0])
        : "cc");
    asm("addq %2,%0; adcq %3,%1"  
        : "+r"(carry), "+d"(high) 
        : "a"(low), "g"(0)        
        : "cc");  
    asm("addq %2,%0; adcq %3,%1"  
        : "+m"(ap[0]), "+d"(high)     
        : "r"(carry), "g"(0)      
        : "cc");          

    return high;
}

int main(void) {
    BN_ULONG a[1];
    a[0] = 0xFFFFFFFFFFFFFFFFUL;

    BN_ULONG r = mul_high(a, 2);


    printf("OK\n");
    return 0;
}
