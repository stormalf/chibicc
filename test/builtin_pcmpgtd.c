#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = {10, 40};
    v2si b = {20, 30};

    // Compare elements: result is 0xFFFFFFFF (-1) if a[i] > b[i], else 0
    v2si c = __builtin_ia32_pcmpgtd(a, b);

    for (int i = 0; i < 2; i++) {
        printf("%d ", c[i]);  // -1 for true, 0 for false
    }
    printf("\n");

    // Expected output: 0 -1
    ASSERT(0, c[0]);
    ASSERT(-1, c[1]);
    printf("OK\n");
    return 0;
}
