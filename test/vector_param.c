#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

void print_vector(float4 v) {
    for (int i = 0; i < 4; i++) {
        printf("v[%d] = %f\n", i, v[i]);
    }
    ASSERT(11, v[0]);
    ASSERT(22, v[1]);
    ASSERT(33, v[2]);
    ASSERT(44, v[3]);
}

float4 add_vectors(float4 a, float4 b) {
    return a + b;
}

int main() {
    float4 a = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 b = {10.0f, 20.0f, 30.0f, 40.0f};
    float4 c;
    c = add_vectors(a, b);
    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }
    ASSERT(11, c[0]);
    ASSERT(22, c[1]);
    ASSERT(33, c[2]);
    ASSERT(44, c[3]);
    print_vector(c);
    return 0;
}
