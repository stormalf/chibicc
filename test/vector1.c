#include "test.h"
typedef float float4 __attribute__((vector_size(16)));

float4 a = {1.0, 2.0, 3.0, 4.0};
float4 b = {10.0, 20.0, 30.0, 40.0};
float4 c;

typedef int myint;

int main() {
    float4 vec = {1.0, 2.0, 3.0, 4.0};
    printf("vec[0]=%f\n", vec[0]);
    printf("vec[1]=%f\n", vec[1]);
    printf("vec[2]=%f\n", vec[2]);
    printf("vec[3]=%f\n", vec[3]);
    c = a + b;
    printf("after %f %f %f %f\n", c[0], c[1], c[2], c[3]);
    ASSERT(11, c[0]);
    ASSERT(22, c[1]);
    ASSERT(33, c[2]);
    ASSERT(44, c[3]);

    myint x = 42;
    printf("x = %d\n", x);
    ASSERT(42, x);

    int a[4] = {1, 2, 3, 4};
    int b[4] = {10, 20, 30, 40};
    int c[4];

    for (int i = 0; i < 4; i++)
        c[i] = a[i] + b[i];

    for (int i = 0; i < 4; i++)
        printf("c[%d] = %d\n", i, c[i]);

    return 0;
}