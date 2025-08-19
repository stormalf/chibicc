#include "test.h"
typedef float  __v4sf __attribute__((vector_size(16)));

int main() {
    __v4sf a = {3.0f, 100.0f, 200.0f, 300.0f};
    __v4sf b = {5.0f, 400.0f, 500.0f, 600.0f};

    __v4sf res = __builtin_ia32_minss(a, b);

    float *f = (float *)&res;
    for (int i = 0; i < 4; i++)
        printf("res[%d] = %f\n", i, f[i]);

    ASSERT(3, res[0]);
    ASSERT(100, res[1]);
    ASSERT(200, res[2]);
    ASSERT(300, res[3]);
    printf("OK\n");
    return 0;
}
