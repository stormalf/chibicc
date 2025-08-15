#include "test.h"

typedef double v2df __attribute__((vector_size(16)));

int main() {
    v2df val = { 1.25, -2.5 };
    double dst[2] = {0.0, 0.0};

    // Non-temporal store 128-bit packed doubles to dst
    __builtin_ia32_movntpd(dst, val);

    printf("%.2f %.2f\n", dst[0], dst[1]); // expect: 1.25 -2.50
    
    ASSERT(1, dst[0]);
    ASSERT(-2, dst[1]);
    printf("OK\n");
    return 0;
}
