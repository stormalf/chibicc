#include "test.h"
#include <stdint.h>

typedef char v16qi __attribute__((vector_size(16)));

v16qi do_psubsb(v16qi a, v16qi b) {
    // Saturated subtraction of packed signed 8-bit integers
    return __builtin_ia32_psubsb128(a, b);
}

int main() {
    v16qi a = { 120, 100, -120, -100, 50, -50, 127, -127,
                 10,  20,  -30,   40,  90, -90,  60, -60 };

    v16qi b = { 10, 50, -50, 100, -100, -100, -1, 1,
                -10,  30,   40,  -50,  -90,  90, -70, 70 };

    v16qi result = do_psubsb(a, b);

    printf("Result: ");
    for (int i = 0; i < 16; i++)
        printf("%d ", result[i]);

    ASSERT(110, result[0]);
    ASSERT(50, result[1]);
    ASSERT(-70, result[2]);
    ASSERT(-128, result[3]);
    ASSERT(127, result[4]);
    ASSERT(50, result[5]);
    ASSERT(127, result[6]);
    ASSERT(-128, result[7]);
    ASSERT(20, result[8]);
    ASSERT(-10, result[9]);
    ASSERT(-70, result[10]);
    ASSERT(90, result[11]);
    ASSERT(127, result[12]);
    ASSERT(-128, result[13]);
    ASSERT(127, result[14]);
    ASSERT(-128, result[15]);

    printf("\n");

    return 0;
}
