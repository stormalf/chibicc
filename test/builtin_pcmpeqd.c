#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = {10, 20};
    v2si b = {10, 30};

    // Compare elements: result is 0xFFFFFFFF (-1) if equal, else 0x00000000
    v2si c = __builtin_ia32_pcmpeqd(a, b);

    for (int i = 0; i < 2; i++) {
        printf("%d ", c[i]);  // -1 for true, 0 for false
    }
    printf("\n");

    // Expected output: -1 0
    ASSERT(-1, c[0]);
    ASSERT(0, c[1]);
    printf("OK\n");
    return 0;
}
