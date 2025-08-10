#include "test.h"

typedef float  __m128 __attribute__((vector_size(16)));

int main(void) {
    __m128 vec = {4.0f, 9.0f, 16.0f, 25.0f};
    __m128 result = __builtin_ia32_sqrtps(vec);


    printf("sqrt results: %f %f %f %f\n", result[0], result[1], result[2], result[3]);
    ASSERT(2, result[0]);
    ASSERT(3, result[1]);
    ASSERT(4, result[2]);
    ASSERT(5, result[3]);
    printf("OK\n");
    return 0;
}
