#include "test.h"
#include <stdint.h>

typedef int int4 __attribute__((vector_size(16)));       // 4×int
typedef float float4 __attribute__((vector_size(16)));   // 4×float
typedef double double2 __attribute__((vector_size(16))); // 2×double

int main(void) {
    // int vector + scalar
    int4 vi = {1, 2, 3, 4};
    int4 res_i = vi + 5; // scalar 5 promoted to {5,5,5,5}
    for (int i =0; i < 4 ; i++)
        printf("res[%d]=%d ", i, res_i[i]);

    printf("\n");
    // ASSERT(6, res_i[0]);
    // ASSERT(7, res_i[1]);
    // ASSERT(8, res_i[2]);
    // ASSERT(9, res_i[3]);

    // float vector + scalar
    float4 vf = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 res_f = vf + 1.5f; // scalar promoted to {1.5,1.5,1.5,1.5}
        for (int i =0; i < 4 ; i++)
        printf("res[%d]=%f ", i, res_f[i]);

    printf("\n");
    // ASSERT(2.5f, res_f[0]);
    // ASSERT(3.5f, res_f[1]);
    // ASSERT(4.5f, res_f[2]);
    // ASSERT(5.5f, res_f[3]);

    // double vector + scalar
    double2 vd = {1.0, 2.0};
    double2 res_d = vd + 3.0; // scalar promoted to {3.0,3.0}
    // ASSERT(4.0, res_d[0]);
    // ASSERT(5.0, res_d[1]);
        for (int i =0; i < 2 ; i++)
        printf("res[%d]=%f ", i, res_d[i]);

    printf("\n");    

    // chained: scalar + vector
    int4 res_i2 = 10 + vi; // scalar promoted to {10,10,10,10}
    // ASSERT(11, res_i2[0]);
    // ASSERT(12, res_i2[1]);
    // ASSERT(13, res_i2[2]);
    // ASSERT(14, res_i2[3]);
    for (int i =0; i < 4 ; i++)
        printf("res[%d]=%d ", i, res_i2[i]);

    printf("\n");

    printf("Scalar to vector promotion OK\n");
    return 0;
}
