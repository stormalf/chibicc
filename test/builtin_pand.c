#include "test.h"

typedef int v2si __attribute__((vector_size(8)));
typedef v2si __m64;

int main() {
    __m64 a = {0xF0F0F0F0, 0xF0F0F0F0};
    __m64 b = {0x0F0F0F0F, 0x0F0F0F0F};

    __m64 result = __builtin_ia32_pand(a, b);

    printf("a[0]      = 0x%x\n", a[0]);
    printf("a[1]      = 0x%x\n", a[1]);
    printf("b[0]      = 0x%x\n", b[0]);
    printf("b[1]      = 0x%x\n", b[1]);
    printf("result[0] = 0x%x\n", result[0]);
    printf("result[1] = 0x%x\n", result[1]);

    if (result[0] == 0 && result[1] == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
        return 1;
    }
    ASSERT(0xf0f0f0f0, a[0]);
    ASSERT(0xf0f0f0f0, a[1]);
    ASSERT(0xf0f0f0f, b[0]);
    ASSERT(0xf0f0f0f, b[1]);
    ASSERT(0x0, result[0]);
    ASSERT(0x0, result[1]);

    printf("OK\n");
    return 0;
}
