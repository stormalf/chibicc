#include "test.h"

typedef double v2df __attribute__((vector_size(16))); // 2 doubles
typedef int mm64 __attribute__((vector_size(8))); // MMX 64-bit

mm64 test_cvttpd2pi(v2df a) {
    return __builtin_ia32_cvttpd2pi(a);
}

int main(void) {
    v2df input = { 3.9, -2.7 };
    mm64 output = test_cvttpd2pi(input);
    int *p = (int*)&output;
    printf("%d %d\n", p[0], p[1]); // truncated values

    ASSERT(3, p[0]);
    ASSERT(-2, p[1]);
    printf("OK\n");
    return 0;
}
