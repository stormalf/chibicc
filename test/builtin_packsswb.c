#include "test.h"

typedef short v4hi __attribute__((vector_size(8)));   // 4 × 16-bit = 8 bytes
typedef signed char v8qi __attribute__((vector_size(8))); // 8 × 8-bit  = 8 bytes

int main(void) {
    v4hi a = {30000, -30000, 100, -100};
    v4hi b = {32767, -32768, 200, -200};

    // MMX builtin returns an 8-byte vector of signed char
    v8qi result = (v8qi)__builtin_ia32_packsswb(a, b);
    ASSERT(30000, a[0]);
    ASSERT(-30000, a[1]);
    ASSERT(100, a[2]);
    ASSERT(-100, a[3]);
    ASSERT(32767, b[0]);
    ASSERT(-32768, b[1]);
    ASSERT(200, b[2]);
    ASSERT(-200, b[3]);
    for (int i = 0; i < 8; i++)
        printf("%d ", (int)result[i]);
    printf("\n");
    ASSERT(127, result[0]);
    ASSERT(-128, result[1]);
    ASSERT(100, result[2]);
    ASSERT(-100, result[3]);
    ASSERT(127, result[4]);
    ASSERT(-128, result[5]);
    ASSERT(127, result[6]);
    ASSERT(-128, result[7]);
    return 0;
}
