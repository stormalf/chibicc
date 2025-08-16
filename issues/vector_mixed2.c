#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

float4 mix_params(float a, float4 v, float b) {
    return v + (float4){a, b, a, b};
}

float4 sub_mix_params(float a, float4 v, float b) {
    return (float4){a, b, a, b} - v;
}

float4 sub_mix_params2(float a, float4 v, float b) {
    return  v - (float4){a, b, a, b} ;
}


int main() {
    float4 res = mix_params(1.0f, (float4){2,4,6,8}, 3.0f);
    for (int i = 0; i < 4; i++)
        printf("res[%d] = %f\n", i, res[i]);

    ASSERT(3, (int)res[0]);  
    ASSERT(7, (int)res[1]);  
    ASSERT(7, (int)res[2]);  
    ASSERT(11, (int)res[3]); 

    res = sub_mix_params(1.0f, (float4){2,4,6,8}, 3.0f);
    for (int i = 0; i < 4; i++)
        printf("res[%d] = %f\n", i, res[i]);


    res = sub_mix_params2(1.0f, (float4){2,4,6,8}, 3.0f);
    for (int i = 0; i < 4; i++)
        printf("res[%d] = %f\n", i, res[i]);

    float4 x = {1.0, -2.0, 3.0, -4.0};
    float4 r = -x;   // negate the vector

    printf("%f %f %f %f\n", r[0], r[1], r[2], r[3]);
    

    printf("OK\n");
    return 0;
}
