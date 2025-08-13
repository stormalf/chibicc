#include "test.h"

typedef double v2df __attribute__((vector_size(16)));


int main(void) {
    v2df a = { 1.0, 4.0 };
    v2df b = { 3.0, 2.0 };

    v2df c = __builtin_ia32_orpd(a, b);

    // Print the raw bits as unsigned long long to see AND effect
    unsigned long long *p = (unsigned long long *)&c;
    printf("orpd: 0x%llx 0x%llx\n", p[0], p[1]);

    ASSERT(0, p[0]);
    ASSERT(0, p[1]);
    v2df d = __builtin_ia32_orpd(a, b);
     unsigned long long *q = (unsigned long long *)&d;
    ASSERT(0, q[0]);
    ASSERT(0, q[1]);
    printf("OK\n");
    return 0;
}
