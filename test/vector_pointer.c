#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

void add_vectors_ptr(const float4 *a, const float4 *b, float4 *res) {
    *res = *a + *b;
}

int main() {
    float4 a = {1, 2, 3, 4};
    float4 b = {10, 20, 30, 40};
    float4 c;
    add_vectors_ptr(&a, &b, &c);
    printf("c = %f %f %f %f\n", c[0], c[1], c[2], c[3]);
    ASSERT(11, (int)c[0]);
    ASSERT(22, (int)c[1]);
    ASSERT(33, (int)c[2]);
    ASSERT(44, (int)c[3]);
}
