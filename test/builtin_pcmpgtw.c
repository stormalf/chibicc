#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));

int main() {
    v4hi a = {5, 2, 7, 1};
    v4hi b = {3, 4, 7, 0};

    // Compare elements: result is 0xFFFF (-1) if a[i] > b[i], else 0x0000
    v4hi c = __builtin_ia32_pcmpgtw(a, b);

    for (int i = 0; i < 4; i++) {
        printf("%d ", (short)c[i]);  // -1 for true, 0 for false
    }
    printf("\n");

    // Expected output: -1 0 0 -1
    ASSERT(-1, c[0]);
    ASSERT(0, c[1]);
    ASSERT(0, c[2]);
    ASSERT(-1, c[3]);

    printf("OK\n");
    return 0;
}
