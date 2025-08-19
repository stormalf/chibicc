#include "test.h"

typedef float __m128 __attribute__((vector_size(16)));
typedef int   __m64  __attribute__((vector_size(8)));

__m64 my_cvtps2pi(__m128 a) {
    return __builtin_ia32_cvtps2pi(a);
}

int main() {
    __m128 floats = {1.5f, 2.5f, 3.5f, 4.5f};
    __m64 ints = my_cvtps2pi(floats);

    printf("floats =%f %f %f %f\n", floats[0], floats[1], floats[2], floats[3]);
    ASSERT(1, floats[0]);
    ASSERT(2, floats[1]);
    ASSERT(3, floats[2]);
    ASSERT(4, floats[3]);

    printf("Converted ints: %d %d\n", (int)ints[0], (int)ints[1]);
    ASSERT(2, (int)ints[0]);
    ASSERT(2, (int)ints[1]);
    return 0;
}
