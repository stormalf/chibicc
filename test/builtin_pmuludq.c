#include "test.h"
#include <stdint.h>

typedef int v4li __attribute__((vector_size(8)));
typedef unsigned long long v4lu __attribute__((vector_size(8)));

int main() {

    v4li  a =  { 2, 4};
    v4li b =  { 10, 20};

    // Multiply and keep the high 16 bits
    v4lu vc = (v4lu)__builtin_ia32_pmuludq(a, b); // intrinsic for PMULHW

    printf("Result: %llu\n", (unsigned long long)vc[0]);
    ASSERT(20, vc[0]);
    printf("OK\n");
    return 0;
}
