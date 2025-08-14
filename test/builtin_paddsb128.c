#include "test.h"
#include <stdint.h>

typedef char __v16qi __attribute__((__vector_size__(16)));

__v16qi paddsb128(__v16qi a, __v16qi b) {
    return __builtin_ia32_paddsb128(a, b);
}

int main() {
    // Signed 8-bit integers: will saturate at 127 and -128
    __v16qi a = {120, -125, 60, -60, 100, -100, 50, -50,
                 127, -128, 10, -10, 30, -30, 80, -80};
    __v16qi b = {10, -10, 70, -70, 50, -50, 100, -100,
                 1, -1, 120, -120, -50, 50, 60, -60};

    __v16qi r = paddsb128(a, b);

    int8_t *vals = (int8_t *)&r;
    for (int i = 0; i < 16; i++)
        printf("%d ", vals[i]);

    printf("\n");

    ASSERT(127, r[0]);
    ASSERT(-128, r[1]);
    ASSERT(127, r[2]);
    ASSERT(-128, r[3]);
    ASSERT(127, r[4]);
    ASSERT(-128, r[5]);
    ASSERT(127, r[6]);
    ASSERT(-128, r[7]);
    ASSERT(127, r[8]);
    ASSERT(-128, r[9]);
    ASSERT(127, r[10]);
    ASSERT(-128, r[11]);
    ASSERT(-20, r[12]);
    ASSERT(20, r[13]);
    ASSERT(127, r[14]);
    ASSERT(-128, r[15]);
    printf("OK\n");
    return 0;
}
