#include "test.h"
#include <stdint.h>

typedef unsigned long BN_ULONG;

static BN_ULONG mul_test(BN_ULONG *ap, BN_ULONG w)
{
    BN_ULONG high, low;
    BN_ULONG result;

    asm("mulq %3"
        : "=a"(low), "=d"(high)
        : "a"(w), "m"(ap[0])
        : "cc");

    result = high;
    return result;
}

int main(void)
{
    BN_ULONG a[4] = {0xFFFFFFFFFFFFFFFFUL, 1, 2, 3};
    BN_ULONG r = mul_test(a, 2);
    printf("%ld\n", r);
    printf("OK\n");
    return 0;
}