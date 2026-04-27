#include "test.h"

typedef unsigned __int128 uint128;

// External assembly function
extern void validate_abi_state(void);

/*
 * This function is designed to pressure chibicc's register allocator.
 * It holds many live variables across the call to assembly.
 */
void test_abi_compliance(unsigned long input) {
    unsigned long a = input;
    unsigned long b = input + 1;
    unsigned long c = input + 2;
    unsigned long d = input + 3;
    unsigned long e = input + 4;
    
    // Generate 128-bit values to force usage of RAX:RDX and stack spills
    uint128 big1 = (uint128)a * b;
    uint128 big2 = (uint128)c * d;
    
    // This complex expression forces 'depth' tracking in codegen.c to work.
    // If depth is tracked incorrectly with -f-omit-frame-pointer, 
    // the stack will be misaligned before the call below.
    unsigned long intermediate = (a + b + c) * (d - e) / (a | 1);
    
    printf("Calling assembly validator (intermediate: %lu)...\n", intermediate);
    
    // CRITICAL POINT: 
    // 1. If depth tracking is wrong -> Segfault inside validate_abi_state.
    // 2. If register clobbering is occurring -> 'a', 'b', 'c', etc. will change.
    validate_abi_state();

    printf("Returned from assembly safely.\n");

    // Verify that our variables weren't clobbered by the "poison" in assembly
    ASSERT(input, a);
    ASSERT(input + 1, b);
    ASSERT(input + 2, c);
    ASSERT(input + 3, d);
    ASSERT(input + 4, e);
    
    // Verify 128-bit results survived
    ASSERT((unsigned long)(big1 & 0xFFFFFFFFFFFFFFFF), (unsigned long)((uint128)input * (input + 1)));
}

int main() {
    test_abi_compliance(100);
    printf("OK\n");
    return 0;
}