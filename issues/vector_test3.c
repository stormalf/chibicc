//#include "test.h"
#include <string.h>
#include <stdio.h>

typedef float float4a1 __attribute__((__vector_size__(16), __aligned__(1)));
typedef float float4 __attribute__((__vector_size__(16)));

void process_vector(float4a1 *vec) {
    for (int i = 0; i < 4; i++) {
        printf("vec[%d] = %f\n", i, vec[i]);
    }
}

int main(void) {
    // float4 v1;
    // float4 v2;
    float4a1 v3 = {12, 2, 3, 14};
    float4a1 v4 = { 1, 1, 1, 1 };
    float4a1 v5 = v3 + v4;
    for (int i = 0; i < 4; i++) {
        printf("v5[%d] = %f\n", i, v5[i]);
    }
    // float x[4] = {1, 2, 3, 4};
    // float y[4] = {1, 1, 1, 1};
    
    // memcpy(&v1, x, 16);
    // memcpy(&v2, y, 16);
    // v1 = v1 + v2;
    // for (int i = 0; i < 4; i++) {
    //     printf("v1[%d] = %f\n", i, v1[i]);
    // }

    return 0;
}
