#include "test.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

typedef unsigned __int128 uint128_t;
typedef unsigned long BN_ULONG;

#if (defined(__x86_64) || defined(__x86_64__))
#if defined(__GNUC__) && __GNUC__ >= 2
#define BN_UMULT_HIGH(a, b) ({     \
        register BN_ULONG ret,discard;  \
        asm ("mulq      %3"             \
             : "=a"(discard),"=d"(ret)  \
             : "a"(a), "g"(b)           \
             : "cc");                   \
        ret; })
#define BN_UMULT_LOHI(low, high, a, b) \
    asm("mulq      %3"                 \
        : "=a"(low), "=d"(high)        \
        : "a"(a), "g"(b)               \
        : "cc");
#endif
#endif

/* one iteration like bn_mul_words */
static BN_ULONG step(BN_ULONG a, BN_ULONG w, BN_ULONG *carry) {
    BN_ULONG low, high;

    BN_UMULT_LOHI(low, high, w, a);

    BN_ULONG ret = low + *carry;
    BN_ULONG c = high + (ret < low);

    *carry = c;
    return ret;
}

/* full chain like bn_mul_words */
static void chain(BN_ULONG *r, BN_ULONG *a, BN_ULONG w, int n) {
    BN_ULONG carry = 0;

    for (int i = 0; i < n; i++) {
        r[i] = step(a[i], w, &carry);
    }

    r[n] = carry;
}

/* reference using __int128 */
static void ref(BN_ULONG *r, BN_ULONG *a, BN_ULONG w, int n) {
    __uint128_t carry = 0;

    for (int i = 0; i < n; i++) {
        __uint128_t t = (__uint128_t)a[i] * w + carry;
        r[i] = (BN_ULONG)t;
        carry = t >> 64;
    }

    r[n] = (BN_ULONG)carry;
}

static void test_once() {
    const int N = 8;

    BN_ULONG a[N];
    BN_ULONG r1[N+1];
    BN_ULONG r2[N+1];

    for (int i = 0; i < N; i++)
        a[i] = ((BN_ULONG)rand() << 32) ^ rand();

    BN_ULONG w = ((BN_ULONG)rand() << 32) ^ rand();

    chain(r1, a, w, N);
    ref(r2, a, w, N);

    for (int i = 0; i < N+1; i++) {
        if (r1[i] != r2[i]) {
            printf("FAIL at %d\n", i);
            printf("w=%lx\n", w);
            for (int j = 0; j < N; j++)
                printf("a[%d]=%lx\n", j, a[j]);

            printf("got:\n");
            for (int j = 0; j < N+1; j++)
                printf("%lx ", r1[j]);
            printf("\nwant:\n");
            for (int j = 0; j < N+1; j++)
                printf("%lx ", r2[j]);
            printf("\n");

            exit(1);
        }
    }
}

int main() {
    for (int i = 0; i < 100000; i++)
        test_once();

    printf("OK\n");
    return 0;
}
