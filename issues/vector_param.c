#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

void print_vector(float4 v) {
    for (int i = 0; i < 4; i++) {
        printf("v[%d] = %f\n", i, v[i]);
    }
}

float4 add_vectors(float4 a, float4 b) {
    return a + b;
}

int main() {
    float4 a = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 b = {10.0f, 20.0f, 30.0f, 40.0f};
    float4 c = add_vectors(a, b);

    print_vector(c);
    return 0;
}
