#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

int main() {
    float4 a = {1.0f, 2.0f, 3.0f, 4.0f};
    float4 b = {10.0f, 20.0f, 30.0f, 40.0f};
    float4 c;
    c = a + b;

    for (int i = 0; i < 4; i++) {
        printf("c[%d] = %f\n", i, c[i]);
    }
    ASSERT(11, c[0]);
    ASSERT(22, c[1]);
    ASSERT(33, c[2]);
    ASSERT(44, c[3]);

    // test 1: expression
    float4 a, b, c;
    a = (float4){1, 2, 3, 4};
    b = (float4){10, 20, 30, 40};
    c = a + b;  

    // test 2: brace init
    float4 d = {100, 200, 300, 400};  

    return 0;
}
