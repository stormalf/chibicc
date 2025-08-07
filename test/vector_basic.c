#include "test.h"
typedef float float4 __attribute__((vector_size(16)));

float4 make_vec() {
    return (float4){1.0f, 2.0f, 3.0f, 4.0f}; // compound literal for vector
}
float make_float() {
    return (float){1.0f}; // compound literal for vector
}

int main() {
    float4 v = make_vec();
    float4 z;
    float4 a = {1.0f, 11.0f, 111.0f, 1111.0f };
    float4 b = {2.0f, 22.0f, 222.0f, 2222.0f};
    float4 d = {1.1f, 2.2f, 3.3f, 4.4f};
    float f= 12.0f;
    float g = 7.0f;
    float h = make_float();
    float i;
    i = f + g + h;
    float4 c;
    c = a + b + d ;

    float4 j = a + b + d;
    z = make_vec();
    printf("v=%f %f %f %f\n", v[0], v[1], v[2], v[3]);
    ASSERT(1, v[0]);
    ASSERT(2, v[1]);
    ASSERT(3, v[2]);
    ASSERT(4, v[3]);
    printf("c= %f %f %f %f\n", c[0], c[1], c[2], c[3]);
    ASSERT(3, c[0]);
    ASSERT(24, c[1]);
    ASSERT(225, c[2]);
    ASSERT(2226, c[3]);
    printf("i=%f\n", i);
    ASSERT(20, i);
    printf("z=%f %f %f %f\n", z[0], z[1], z[2], z[3]);
    ASSERT(1, z[0]);
    ASSERT(2, z[1]);
    ASSERT(3, z[2]);
    ASSERT(4, z[3]);
    printf("a=%f %f %f %f\n", a[0], a[1], a[2], a[3]);
    ASSERT(1, a[0]);
    ASSERT(11, a[1]);
    ASSERT(111, a[2]);
    ASSERT(1111, a[3]);
    printf("j=%f %f %f %f\n", j[0], j[1], j[2], j[3]);
    ASSERT(3, j[0]);
    ASSERT(24, j[1]);
    ASSERT(225, j[2]);
    ASSERT(2226, j[3]);
}
