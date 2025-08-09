#include "test.h"

typedef int v2si __attribute__((vector_size(8)));  // 2 ints, 64 bits (MMX size)

int main() {
    v2si a = {1000, 2000};
    v2si b = {10, 20};
    ASSERT(1000, a[0]);
    ASSERT(2000, a[1]);
    ASSERT(10, b[0]);
    ASSERT(20, b[1]);

    v2si result = __builtin_ia32_punpckhdq(a, b);

    for (int i = 0; i < 2; i++) {
        printf("%d ", result[i]);
    }
    ASSERT(2000, result[0]);
    ASSERT(20, result[1]);
    printf("OK\n");
    return 0;
}
