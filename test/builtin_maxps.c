#include "test.h"
typedef float  __v4sf __attribute__((vector_size(16)));

int main(void) {
    __v4sf a= {1.5f, 2.0f, 3.0f, 4.0f};
    __v4sf b = {3.5f, 1.0f, 5.0f, 6.0f};
    
    __v4sf out = __builtin_ia32_maxps(a, b);

    
    printf("Result: %f %f %f %f\n", out[0], out[1], out[2], out[3]);
    ASSERT(3, out[0]);
    ASSERT(2, out[1]);
    ASSERT(5, out[2]);
    ASSERT(6, out[3]);
    printf("OK\n");
    return 0;
}