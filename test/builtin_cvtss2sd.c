#include "test.h"

typedef float  v4sf __attribute__((vector_size(16))); // 4 floats
typedef double v2df __attribute__((vector_size(16))); // 2 doubles

int main(void) {
    v4sf a = { 3.5f, 99.0f, 0.0f, 0.0f };  // source float vector
    v2df b = { 1.25, 2.5 };                // destination double vector

    // Convert low float in `a` to double, replacing low double in `b`
    v2df res = __builtin_ia32_cvtss2sd(b, a);

    printf("result: %.10f %.10f\n", res[0], res[1]);
    ASSERT(3, res[0]);
    ASSERT(2, res[1]);
    printf("OK\n");
    return 0;
}
