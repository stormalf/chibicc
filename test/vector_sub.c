#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

int main() {
    float4 a = {10.0f, 20.0f, 30.0f, 40.0f};
    float4 b = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 c = a - b;

    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }
    ASSERT(9, c[0]);
    ASSERT(18, c[1]);
    ASSERT(27, c[2]);
    ASSERT(36, c[3]);
    return 0;
}
