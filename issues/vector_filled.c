#include "test.h"

typedef float float4 __attribute__((vector_size(16)));

float4 add_all(float4 a, float4 b, float4 c, float4 d, float4 e, float4 f, float4 g, float4 h) {
    return a + b + c + d + e + f + g + h;
    //return a + b + c;
}

int main() {
    float4 v = add_all(
        (float4){1,2,3,4}, (float4){10,20,30,40},
        (float4){5,6,7,8}, (float4){9,10,11,12},
        (float4){13,14,15,16}, (float4){17,18,19,20},
        (float4){21,22,23,24}, (float4){25,26,27,28}
    );
    printf("v = %f %f %f %f\n", v[0], v[1], v[2], v[3]);
    ASSERT(101, (int)v[0]);
    ASSERT(118, (int)v[1]);
    ASSERT(135, (int)v[2]);
    ASSERT(152, (int)v[3]);
}
