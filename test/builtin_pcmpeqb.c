#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));
typedef unsigned char v8qu __attribute__((vector_size(8)));

int main() {
    v8qi a = {1, 2, 3, 4, 5, 6, 7, 8};
    v8qi b = {1, 0, 3, 0, 5, 0, 7, 0};

    // Compare each byte for equality, returns 0xFF in each byte if equal, else 0x00
    v8qu c = (v8qu)__builtin_ia32_pcmpeqb(a, b);

    // Print bytes as unsigned integers
    for (int i = 0; i < 8; i++) {
        printf("%u ", (unsigned char)c[i]);
    }
    printf("\n");

    // Expected output: 255 0 255 0 255 0 255 0
    ASSERT(255, c[0]);
    ASSERT(0, c[1]);
    ASSERT(255, c[2]);
    ASSERT(0, c[3]);
    ASSERT(255, c[4]);
    ASSERT(0, c[5]);
    ASSERT(255, c[6]);
    ASSERT(0, c[7]);

    printf("OK\n");
    return 0;
}
