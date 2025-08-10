#include "test.h"

typedef char v8qi __attribute__((vector_size(8)));

int main() {
    v8qi a = {1, 5, -3, 4, 127, -128, 7, -1};
    v8qi b = {1, 2, -5, 4, 126, -128, 8, 0};

    // Compare bytes, returns 0xFF if a[i] > b[i], else 0x00
    v8qi c = __builtin_ia32_pcmpgtb(a, b);

    for (int i = 0; i < 8; i++) {
        printf("%d ", (signed char)c[i]);  // Will print either 0 or -1 (0xFF)
    }
    printf("\n");

    // Expected output: 0 -1 -1 0 -1 0 0 -1
    ASSERT(0, c[0]);
    ASSERT(-1, c[1]);
    ASSERT(-1, c[2]);
    ASSERT(0, c[3]);
    ASSERT(-1, c[4]);
    ASSERT(0, c[5]);
    ASSERT(0, c[6]);
    ASSERT(0, c[7]);
    printf("OK\n");
    return 0;
}
