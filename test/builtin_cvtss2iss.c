#include "test.h"

// Manually declare the builtin (no xmmintrin.h included)
typedef float __v4sf __attribute__((vector_size(16)));

__v4sf __builtin_ia32_cvtsi2ss(__v4sf a, int b);

int main(void) {
    __v4sf vec = { 1.0f, 2.0f, 3.0f, 4.0f };
    int val = 123;

    __v4sf result = __builtin_ia32_cvtsi2ss(vec, val);

    printf("Original vector first element: %.2f\n", vec[0]);
    printf("Inserted int as float: %.2f\n", result[0]);
    printf("Other elements unchanged: %.2f, %.2f, %.2f\n",
           result[1], result[2], result[3]);
    ASSERT(123, result[0]);
    ASSERT(1, vec[0]);
    if ((int)result[0] == val && result[1] == vec[1]) {
        puts("PASS");
        return 0;
    } else {
        puts("FAIL");
        return 1;
    }
}
