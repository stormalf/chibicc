
#include "test.h"

typedef int __v4si __attribute__((vector_size(16)));
typedef double     __v2df __attribute__((vector_size(16)));

int main() {
    __v4si src = { 42, -100 , 80, -200}; // actually only low 64 bits used here

    __v2df result = __builtin_ia32_cvtdq2pd((__v4si)src);

    printf("result[0] = %f\n", result[0]);
    printf("result[1] = %f\n", result[1]);
    ASSERT(42, result[0]);
    ASSERT(-100, result[1]);
    printf("OK\n");
    return 0;
}
