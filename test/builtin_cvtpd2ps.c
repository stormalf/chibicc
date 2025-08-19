#include "test.h"
typedef float  __v4sf __attribute__((vector_size(16)));
typedef double __v2df __attribute__((vector_size(16)));

__v4sf test_cvtpd2ps(__v2df a) {
    return (__v4sf)__builtin_ia32_cvtpd2ps(a);
}

#include <stdio.h>
int main() {
    __v2df a = { 1.5, -2.25 };
    __v4sf r = test_cvtpd2ps(a);
    printf("%f %f\n", r[0], r[1]); // upper 2 floats are undefined
    ASSERT(1, r[0]);
    ASSERT(-2, r[1]);
    ASSERT(0, r[2]);
    ASSERT(0, r[3]);
    printf("OK\n");
    return 0;
}
