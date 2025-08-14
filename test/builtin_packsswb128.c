// test_packsswb128.c

#include "test.h"

typedef short __v8hi __attribute__((vector_size(16)));
typedef char  __v16qi __attribute__((vector_size(16)));
typedef __v16qi __m128i;

// Declare the builtin explicitly so Chibicc knows it
extern __v16qi __builtin_ia32_packsswb128(__v8hi, __v8hi);

__m128i test_packsswb128(__v8hi a, __v8hi b) {
    return (__m128i)__builtin_ia32_packsswb128(a, b);
}

int main(void) {
    __v8hi a = { 100, 200, 30000, -30000, -200, -150, 127, -128 };
    __v8hi b = { 50, -50, 40000, -40000, 200, 150, -127, 128 };

    __m128i r = test_packsswb128(a, b);

    char *bytes = (char *)&r;
    printf("Result bytes:\n");
    for (int i = 0; i < 16; i++) {
        printf("%d ", bytes[i]);
    }
    printf("\n");
    ASSERT(100, r[0]);
    ASSERT(127, r[1]);
    ASSERT(127, r[2]);
    ASSERT(-128, r[3]);
    ASSERT(-128, r[4]);
    ASSERT(-128, r[5]);
    ASSERT(127, r[6]);
    ASSERT(-128, r[7]);
    ASSERT(50, r[8]);
    ASSERT(-50, r[9]);
    ASSERT(-128, r[10]);
    ASSERT(127, r[11]);
    ASSERT(127, r[12]);
    ASSERT(127, r[13]);
    ASSERT(-127, r[14]);
    ASSERT(127, r[15]);
    printf("OK\n");
    return 0;
}
