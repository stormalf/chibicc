#include "test.h"



unsigned long bn_mul_words(unsigned long *rp, const unsigned long *ap, int num, unsigned long w)
{
    unsigned long c1 = 0;

    if (num <= 0)
        return c1;

    while (num & ~3) {
        {
        register unsigned long high,low;
        asm ("mulq %3"
                : "=a"(low),"=d"(high)
                : "a"(w),"g"(ap[0])
                : "cc");
        }
        ap += 4;
        rp += 4;
        num -= 4;
    }
    return c1;
}

unsigned long test_g_constraint(unsigned long *rp, const unsigned long *ap) {
    unsigned long result;
    asm ("mulq %2"
            : "=a"(result)
            : "a"(5),"g"(0)
            : "cc","rdx");
    return result;
}

int main() {
    unsigned long rp[4] = {0};
    unsigned long ap[4] = {1, 2, 3, 4};
    
    bn_mul_words(rp, ap, 4, 2);
    
    unsigned long r = test_g_constraint(rp, ap);
    if (r != 0) {
        printf("FAIL: expected 0, got %lu\n", r);
        return 1;
    }
    
    printf("PASS\n");
    return 0;
}