
#include "test.h"

typedef int __v4si __attribute__((vector_size(16)));
typedef float     __v4sf __attribute__((vector_size(16)));

int main() {
    __v4si src = { 42, -100 , 80, -200}; // actually only low 64 bits used here

    __v4sf result = __builtin_ia32_cvtdq2ps((__v4si)src);

    printf("result[0] = %f\n", result[0]);
    printf("result[1] = %f\n", result[1]);
    printf("result[2] = %f\n", result[2]);
    printf("result[3] = %f\n", result[3]);    
    ASSERT(42, result[0]);
    ASSERT(-100, result[1]);
    ASSERT(80, result[2]);
    ASSERT(-200, result[3]);    
    printf("OK\n");
    return 0;
}
