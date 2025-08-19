#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

float4 mix_params(float a, float4 v, float b) {
    return (float4){a, b, a, b} + v;
}

int main() {
    float4 res = mix_params(1.0f, (float4){2,4,6,8}, 3.0f);
    for (int i = 0; i < 4; i++)
        printf("res[%d] = %f\n", i, res[i]);

    ASSERT(3, (int)res[0]);  
    ASSERT(7, (int)res[1]);  
    ASSERT(7, (int)res[2]);  
    ASSERT(11, (int)res[3]); 
}
