// asm_array_loop_test.c
#include "test.h"
#include <stdint.h>

typedef unsigned long BN_ULONG;

static BN_ULONG mul_add_loop(BN_ULONG *rp, const BN_ULONG *ap,
                            int n, BN_ULONG w)
{
    BN_ULONG carry = 0;

    for (int i = 0; i < n; i++) {
        BN_ULONG high, low;

        // mul
        asm("mulq %3"
            : "=a"(low), "=d"(high)
            : "a"(w), "m"(ap[i])
            : "cc");

        // add low into carry
        asm("addq %2,%0; adcq %3,%1"
            : "+r"(carry), "+d"(high)
            : "a"(low), "g"(0)
            : "cc");

        // add carry into rp[i]
        asm("addq %2,%0; adcq %3,%1"
            : "+m"(rp[i]), "+d"(high)
            : "r"(carry), "g"(0)
            : "cc");

        carry = high;
    }

    return carry;
}

/* reference */
static BN_ULONG ref(BN_ULONG *rp, const BN_ULONG *ap,
                    int n, BN_ULONG w)
{
    BN_ULONG carry = 0;

    for (int i = 0; i < n; i++) {
        __uint128_t t =
            (__uint128_t)ap[i] * w + rp[i] + carry;

        rp[i] = (BN_ULONG)t;
        carry = (BN_ULONG)(t >> 64);
    }

    return carry;
}

int main(void)
{
    BN_ULONG a[4] = {
        0xFFFFFFFFFFFFFFFFUL,
        0x1,
        0x2,
        0x3
    };

    BN_ULONG r1[4] = {0};
    BN_ULONG r2[4] = {0};

    BN_ULONG c1 = mul_add_loop(r1, a, 4, 2);
    BN_ULONG c2 = ref(r2, a, 4, 2);

    for (int i = 0; i < 4; i++) {
        if (r1[i] != r2[i]) {
            printf("FAIL r[%d]: %lu != %lu\n", i, r1[i], r2[i]);
            return 1;
        }
    }

    if (c1 != c2) {
        printf("FAIL carry: %lu != %lu\n", c1, c2);
        return 1;
    }

    printf("OK\n");
    return 0;
}
