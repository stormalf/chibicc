#include "test.h"
#include <stdint.h>
#include <string.h>



typedef unsigned long BN_ULONG;


#undef mul
#undef mul_add

/*-
 * "m"(a), "+m"(r)      is the way to favor DirectPath µ-code;
 * "g"(0)               let the compiler to decide where does it
 *                      want to keep the value of zero;
 */
#define mul_add(r, a, word, carry)    \
    do {                              \
        register BN_ULONG high, low;  \
        asm("mulq %3"                 \
            : "=a"(low), "=d"(high)   \
            : "a"(word), "m"(a)       \
            : "cc");                  \
        asm("addq %2,%0; adcq %3,%1"  \
            : "+r"(carry), "+d"(high) \
            : "a"(low), "g"(0)        \
            : "cc");                  \
        asm("addq %2,%0; adcq %3,%1"  \
            : "+m"(r), "+d"(high)     \
            : "r"(carry), "g"(0)      \
            : "cc");                  \
        carry = high;                 \
    } while (0)

#define mul(r, a, word, carry)        \
    do {                              \
        register BN_ULONG high, low;  \
        asm("mulq %3"                 \
            : "=a"(low), "=d"(high)   \
            : "a"(word), "g"(a)       \
            : "cc");                  \
        asm("addq %2,%0; adcq %3,%1"  \
            : "+r"(carry), "+d"(high) \
            : "a"(low), "g"(0)        \
            : "cc");                  \
        (r) = carry, carry = high;    \
    } while (0)
#undef sqr
#define sqr(r0, r1, a)       \
    asm("mulq %2"            \
        : "=a"(r0), "=d"(r1) \
        : "a"(a)             \
        : "cc");


/* -----------------------------
 * Reference multiplication
 * ----------------------------- */
void ref_mul(BN_ULONG *r, BN_ULONG *a, int na, BN_ULONG *b, int nb)
{
    memset(r, 0, sizeof(BN_ULONG) * (na + nb));

    for (int i = 0; i < na; i++) {
        BN_ULONG carry = 0;
        for (int j = 0; j < nb; j++) {
            unsigned long long prod =
                (unsigned long long)a[i] * b[j] +
                r[i + j] + carry;

            r[i + j] = (BN_ULONG)prod;
            carry = prod >> 32;
        }
        r[i + nb] += carry;
    }
}

/* -----------------------------
 * Fallback word operations
 * ----------------------------- */
BN_ULONG bn_mul_words(BN_ULONG *r, BN_ULONG *a, int n, BN_ULONG w)
{
    BN_ULONG carry = 0;
    for (int i = 0; i < n; i++) {
        unsigned long long prod =
            (unsigned long long)a[i] * w + carry;
        r[i] = (BN_ULONG)prod;
        carry = prod >> 32;
    }
    return carry;
}


BN_ULONG bn_mul_add_words(BN_ULONG *rp, const BN_ULONG *ap, int num,
    BN_ULONG w)
{
    BN_ULONG c1 = 0;

    if (num <= 0)
        return c1;

    while (num & ~3) {
        mul_add(rp[0], ap[0], w, c1);
        mul_add(rp[1], ap[1], w, c1);
        mul_add(rp[2], ap[2], w, c1);
        mul_add(rp[3], ap[3], w, c1);
        ap += 4;
        rp += 4;
        num -= 4;
    }
    if (num) {
        mul_add(rp[0], ap[0], w, c1);
        if (--num == 0)
            return c1;
        mul_add(rp[1], ap[1], w, c1);
        if (--num == 0)
            return c1;
        mul_add(rp[2], ap[2], w, c1);
        return c1;
    }

    return c1;
}


/* -----------------------------
 * YOUR FUNCTION (unchanged)
 * ----------------------------- */
void bn_mul_normal(BN_ULONG *r, BN_ULONG *a, int na, BN_ULONG *b, int nb)
{
    BN_ULONG *rr;

    if (na < nb) {
        int itmp;
        BN_ULONG *ltmp;

        itmp = na;
        na = nb;
        nb = itmp;
        ltmp = a;
        a = b;
        b = ltmp;
    }

    rr = &(r[na]);

    if (nb <= 0) {
        (void)bn_mul_words(r, a, na, 0);
        return;
    } else {
        rr[0] = bn_mul_words(r, a, na, b[0]);
    }

    for (;;) {
        if (--nb <= 0)
            return;
        rr[1] = bn_mul_add_words(&(r[1]), a, na, b[1]);
        if (--nb <= 0)
            return;
        rr[2] = bn_mul_add_words(&(r[2]), a, na, b[2]);
        if (--nb <= 0)
            return;
        rr[3] = bn_mul_add_words(&(r[3]), a, na, b[3]);
        if (--nb <= 0)
            return;
        rr[4] = bn_mul_add_words(&(r[4]), a, na, b[4]);
        rr += 4;
        r += 4;
        b += 4;
    }
}

/* -----------------------------
 * Test
 * ----------------------------- */
#define MAX 32

int main()
{
    BN_ULONG a[MAX], b[MAX], r1[MAX*2], r2[MAX*2];

    for (int i = 0; i < MAX; i++) {
        a[i] = i + 1;
        b[i] = (i % 7) + 1;
    }

    memset(r1, 0, sizeof(r1));
    memset(r2, 0, sizeof(r2));

    bn_mul_normal(r1, a, 16, b, 16);
    ref_mul(r2, a, 16, b, 16);

    // for (int i = 0; i < 32; i++) {
    //     if (r1[i] != r2[i]) {
    //         printf("FAIL at %d: %lu != %lu\n",
    //                i, r1[i], r2[i]);
    //         return 1;
    //     }
    // }
    printf("%ld\n", r1[0]);
    ASSERT(1, r1[0]);
    printf("%ld\n", r1[1]);
    ASSERT(4, r1[1]);
    printf("%ld\n", r2[0]);
    ASSERT(1, r2[0]);
    printf("%ld\n", r2[1]);
    ASSERT(4, r2[1]);
    printf("OK\n");
    return 0;
}