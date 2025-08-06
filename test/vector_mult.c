#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

float4 mul_vectors(float4 a, float4 b) {
    return a * b;
}

int main() {
    float4 a = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 b = {10.0f, 20.0f, 30.0f, 40.0f};
    float4 c;
    c = mul_vectors(a, b);

    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }
    ASSERT(10, (int)c[0]);
    ASSERT(40, (int)c[1]);
    ASSERT(90, (int)c[2]);
    ASSERT(160, (int)c[3]);
}
