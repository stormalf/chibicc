#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

float4 div_vectors(float4 a, float4 b) {
    return a / b;
}

int main() {
    float4 a = {10.0f, 20.0f, 30.0f, 40.0f};
    float4 b = {2.0f, 4.0f, 5.0f, 8.0f};
    float4 c;
    c = div_vectors(a, b);
    float4 d = {5.0f, 5.0f, 5.0f, 5.0f};
    float4 e = div_vectors(a, d);

    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }
    ASSERT(5, (int)c[0]);
    ASSERT(5, (int)c[1]);
    ASSERT(6, (int)c[2]);
    ASSERT(5, (int)c[3]);
    for (int i = 0; i < 4; i++) {
        printf("e[%d] = %f\n", i, e[i]);
    }
    ASSERT(2, e[0]);
    ASSERT(4, e[1]);
    ASSERT(6, e[2]);
    ASSERT(8, e[3]);
    return 0;
}
