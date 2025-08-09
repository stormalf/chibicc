#include "test.h"

typedef int v2si __attribute__((vector_size(8)));

int main() {
    v2si a = {1, 2};

    // Shift left each 32-bit element by 1 bit (immediate)
    v2si result = __builtin_ia32_pslldi(a, 1);

    for (int i = 0; i < 2; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    ASSERT(1, a[0]);
    ASSERT(2, a[1]);

    ASSERT(2, result[0]);
    ASSERT(4, result[1]);
    printf("OK\n");

    return 0;
}
