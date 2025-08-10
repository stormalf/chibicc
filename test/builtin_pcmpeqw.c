#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {1, 2, 3, 4};
    v4hi b = {1, 0, 3, 5};

    // Compare words for equality: each element is 0xFFFF (-1) if equal, else 0x0000
    v4hi c = __builtin_ia32_pcmpeqw(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", (short)c[i]);  // prints -1 if equal else 0
    }
    printf("\n");

    // Expected output: -1 0 -1 0
    ASSERT(-1, c[0]);
    ASSERT(0, c[1]);
    ASSERT(-1, c[2]);
    ASSERT(0, c[3]);
    printf("OK\n");
    return 0;
}
