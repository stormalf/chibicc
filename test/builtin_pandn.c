#include "test.h"

typedef int v2si __attribute__((vector_size(8)));
typedef v2si __m64;

int main() {
    __m64 a = {0xFFFF0000, 0xAAAA5555};
    __m64 b = {0x0F0F0F0F, 0x12345678};

    __m64 result = __builtin_ia32_pandn(a, b);

    printf("a[0]      = 0x%x\n", a[0]);
    printf("a[1]      = 0x%x\n", a[1]);
    printf("b[0]      = 0x%x\n", b[0]);
    printf("b[1]      = 0x%x\n", b[1]);
    printf("result[0] = 0x%x\n", result[0]);
    printf("result[1] = 0x%x\n", result[1]);

    ASSERT(0xffff0000, a[0]);
    ASSERT(0xaaaa5555, a[1]);
    ASSERT(0xf0f0f0f, b[0]);
    ASSERT(0x12345678, b[1]);

    ASSERT(0xf0f, result[0]);
    ASSERT(0x10140228, result[1]);

    printf("OK\n");
    return 0;
}
