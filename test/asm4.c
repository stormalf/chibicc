#include <stdint.h>
#include "test.h"
int main() {
    uint64_t msr;

    asm volatile ( "rdtsc\n\t"    // Returns the time in EDX:EAX.
            "shl $32, %%rdx\n\t"  // Shift the upper bits left.
            "or %%rdx, %0"        // 'Or' in the lower bits.
            : "=a" (msr)
            :
            : "rdx");

    printf("msr: %lx\n", msr);
    ASSERT(1, msr != 0); 


    // Do other work...

    // Reprint the timestamp
    asm volatile ( "rdtsc\n\t"    // Returns the time in EDX:EAX.
            "shl $32, %%rdx\n\t"  // Shift the upper bits left.
            "or %%rdx, %0"        // 'Or' in the lower bits.
            : "=a" (msr)
            :
            : "rdx");

    printf("msr: %lx\n", msr);
    ASSERT(1, msr != 0); 

    return 0;
}