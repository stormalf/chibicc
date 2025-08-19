#include "test.h"
#include <stdint.h>

typedef int int4 __attribute__((vector_size(16)));  // 4×32-bit integers

int main(void) {
    int4 a = {0x0f0f0f0f, 0x00ff00ff, 0x12345678, 0xffffffff};
    int4 b = {0x00ff00ff, 0x0f0f0f0f, 0x87654321, 0x00000000};
    
    // Bitwise AND
    int4 and_res = a & b;
    printf("AND:  0x%x 0x%x 0x%x 0x%x\n", and_res[0], and_res[1], and_res[2], and_res[3]);

    ASSERT(0xf000f, and_res[0]);
    ASSERT(0xf000f, and_res[1]);
    ASSERT(0x2244220, and_res[2]);
    ASSERT(0x0, and_res[3]);
    // Bitwise OR
    int4 or_res = a | b;
    printf("OR:   0x%x 0x%x 0x%x 0x%x\n", or_res[0], or_res[1], or_res[2], or_res[3]);

    ASSERT(0xfff0fff, or_res[0]);
    ASSERT(0xfff0fff, or_res[1]);
    ASSERT(0x97755779, or_res[2]);
    ASSERT(0xffffffff, or_res[3]);

    // Bitwise XOR
    int4 xor_res = a ^ b;
    printf("XOR:  0x%x 0x%x 0x%x 0x%x\n", xor_res[0], xor_res[1], xor_res[2], xor_res[3]);

    ASSERT(0xff00ff0, xor_res[0]);
    ASSERT(0xff00ff0, xor_res[1]);
    ASSERT( 0x95511559, xor_res[2]);
    ASSERT(0xffffffff, xor_res[3]);    


    // Bitwise NOT
    int4 not_a = ~a;
    printf("NOT a: 0x%x 0x%x 0x%x 0x%x\n", not_a[0], not_a[1], not_a[2], not_a[3]);

    ASSERT(0xf0f0f0f0, not_a[0]);
    ASSERT(0xff00ff00, not_a[1]);
    ASSERT(0xedcba987, not_a[2]);
    ASSERT(0x00000000, not_a[3]);    


    printf("OK\n");
    return 0;
}
