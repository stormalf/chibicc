
//#include "test.h"
#include <string.h>
#include <stdio.h>
typedef float float4a1 __attribute__((__vector_size__(16), __aligned__(1)));
typedef double __v2df __attribute__ ((__vector_size__ (16)));
//typedef long long __v2di __attribute__ ((__vector_size__ (16)));
typedef unsigned int __v4su __attribute__ ((__vector_size__ (16)));
typedef short __v8hi __attribute__ ((__vector_size__ (16)));
typedef unsigned short __v8hu __attribute__ ((__vector_size__ (16)));
typedef char __v16qi __attribute__ ((__vector_size__ (16)));
typedef signed char __v16qs __attribute__ ((__vector_size__ (16)));
typedef unsigned char __v16qu __attribute__ ((__vector_size__ (16)));



void process_vector(float4a1 vec) {
    for (int i = 0; i < 4; i++) {
        printf("vec[%d] = %f\n", i, vec[i]);
        // if (i == 0) {
        //     ASSERT(12.000000, vec[0]);
        // } else if (i == 1) {
        //     ASSERT(2.000000, vec[1]);
        // } else if (i == 2) {
        //     ASSERT(3.000000, vec[2]);
        // } else if (i == 3) {
        //     ASSERT(14.000000, vec[3]);
        // }
    }
}


int main(void) {
    float4a1 v3 = {12, 2, 3, 14};
    for (int i = 0; i < 4; i++) {
        printf("v3[%d] = %f\n", i, v3[i]);
    }
    process_vector(v3);
    printf("ok\n");

  return 0;
}