#include "test.h"

typedef double v2df __attribute__((vector_size(16)));


int main(void) {
    v2df a = { 1.0, 4.0 };
    v2df b = { 1.0, 2.0 };
    v2df d = { 0.8, 3.5 };
    v2df c = __builtin_ia32_cmpgtpd(a, b);

    // Cast to unsigned long long to see raw comparison result bits
    unsigned long long *p = (unsigned long long *)&c;
    printf("cmpgtpd: 0x%llx 0x%llx\n", p[0], p[1]);
    ASSERT(0, p[0]);
    ASSERT(-1, p[1]);
    c = __builtin_ia32_cmpgtpd(d, a);
    p = (unsigned long long *)&c;
    printf("cmpgtpd: 0x%llx 0x%llx\n", p[0], p[1]);
    ASSERT(0, p[0]);
    ASSERT(0, p[1]);
    printf("OK\n");
    return 0;
}
