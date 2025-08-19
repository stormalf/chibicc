#include "test.h"
typedef double  v2df __attribute__((vector_size(16))); // 2 doubles
typedef int     v4si __attribute__((vector_size(16))); // 4 ints

v4si test_truncate(v2df a) {
    return __builtin_ia32_cvttpd2dq(a);
}

#include <stdio.h>

int main(void) {
    v2df input = { 3.9, -2.7 };   // will truncate to {3, -2}
    v4si output = test_truncate(input);
    printf("%d %d %d %d\n", output[0], output[1], output[2], output[3]);
    ASSERT(3, output[0]);
    ASSERT(-2, output[1]);
    ASSERT(0, output[2]);
    ASSERT(0, output[3]);
    printf("OK\n");
    return 0;
}
