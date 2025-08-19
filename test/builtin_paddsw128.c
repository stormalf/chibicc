#include "test.h"

typedef short v8hi __attribute__((vector_size(16)));

v8hi paddsw128_test(v8hi a, v8hi b) {
    return __builtin_ia32_paddsw128(a, b);
}

int main() {
    v8hi a = { 32000, -32000, 20000, -20000, 15000, -15000, 10000, -10000 };
    v8hi b = { 1000, 1000, 20000, 20000, -20000, -20000, 5000, 5000 };
    v8hi r = paddsw128_test(a, b);

    for (int i = 0; i < 8; i++)
        printf("%d ", r[i]);
    printf("\n");

    ASSERT(32767, r[0]);
    ASSERT(-31000, r[1]);
    ASSERT(32767, r[2]);
    ASSERT(0, r[3]);
    ASSERT(-5000, r[4]);
    ASSERT(-32768, r[5]);
    ASSERT(15000, r[6]);
    ASSERT(-5000, r[7]);
    printf("OK\n");

    return 0;
}
