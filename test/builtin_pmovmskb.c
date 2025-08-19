#include "test.h"

typedef char __v8qi __attribute__((vector_size(8)));

int main(void) {
    __v8qi a = {0x80, 0x00, 0xFF, 0x01, 0x00, 0x80, 0x7F, 0x00};

    // Extract MSB of each byte into a mask
    unsigned int mask = (unsigned int)__builtin_ia32_pmovmskb(a);


    printf("mask = 0x%x\n", mask);
    ASSERT(0x25, mask);
    printf("OK\n");

    return 0;
}
