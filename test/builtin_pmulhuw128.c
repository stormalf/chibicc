#include "test.h"

typedef unsigned short ushort8 __attribute__((vector_size(16)));
typedef short short8 __attribute__((vector_size(16)));

int main() {
    // Choose pairs with easy-to-verify products
    short8 a = {0xFFFF, 0x8000, 0x1234, 0xAAAA, 0x00FF, 0x0F0F, 0x7FFF, 0x4000};
    short8 b = {0xFFFF, 0x0002, 0x0010, 0x0002, 0x00FF, 0x1010, 0x0002, 0x4000};

    ushort8 c = (ushort8)__builtin_ia32_pmulhuw128(a, b);

    // Print high 16 bits of each lane product in hex (zero-padded)
    for (int i = 0; i < 8; i++) {
        printf("%04X ", c[i]);
    }
    printf("\n");

    ASSERT(0xFFFE, c[0]);
    ASSERT(0x0001, c[1]);
    ASSERT(0x0001, c[2]);
    ASSERT(0x0001, c[3]);
    ASSERT(0x0000, c[4]);
    ASSERT(0x00F1, c[5]);
    ASSERT(0x0000, c[6]);
    ASSERT(0x1000, c[7]);
    printf("OK\n");
    return 0;
}
