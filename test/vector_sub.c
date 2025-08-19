#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

float4 sub_vectors(float4 a, float4 b) {
    return a - b;
}


int main() {
    float4 a = {10.0f, 20.0f, 30.0f, 40.0f};
    float4 b = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 c;
    c = a - b;

    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }
    ASSERT(9, c[0]);
    ASSERT(18, c[1]);
    ASSERT(27, c[2]);
    ASSERT(36, c[3]);

    float4 d = sub_vectors(a, b);
    ASSERT(9, d[0]);
    ASSERT(18, d[1]);
    ASSERT(27, d[2]);
    ASSERT(36, d[3]);
    return 0;
}
