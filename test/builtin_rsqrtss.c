#include "test.h"

typedef float v4sf __attribute__((vector_size(16)));

extern v4sf __builtin_ia32_rsqrtss(v4sf);

int main(void) {
    v4sf a = { 4.0f, 9.0f, 16.0f, 25.0f };
    v4sf result = __builtin_ia32_rsqrtss(a);

    printf("Input:  %.6f %.6f %.6f %.6f\n", a[0], a[1], a[2], a[3]);
    printf("Output: %.6f %.6f %.6f %.6f\n",
           result[0], result[1], result[2], result[3]);

    ASSERT(0, result[0]);
    ASSERT(9, result[1]);
    ASSERT(16, result[2]);
    ASSERT(25, result[3]);

    printf("OK\n");
    return 0;
}
