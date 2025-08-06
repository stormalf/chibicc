#include "test.h"
typedef float float4 __attribute__((vector_size(16)));

float4 make_vec() {
    return (float4){1.0f, 2.0f, 3.0f, 4.0f}; // compound literal for vector
}

int main() {
    float4 v = make_vec();
    printf("%f %f %f %f\n", v[0], v[1], v[2], v[3]);
}
