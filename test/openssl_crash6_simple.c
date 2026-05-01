/*
 * test_constant_time.c
 *
 * Test suite for value_barrier / constant_time_cond_swap functions.
 * Designed to compile and run under chibicc (a small C11 compiler),
 * which means:
 *   - No GCC inline-asm (__asm__) support  → OPENSSL_NO_ASM path is taken.
 *   - No _Bool / stdbool.h guaranteed, use int for booleans.
 *   - Keep stdio.h + stdint.h as the only headers.
 *   - Avoid VLAs, compound-literals, __builtin_*, and GNU extensions.
 *
 * Build (chibicc):
 *   chibicc -o test_constant_time test_constant_time.c
 *
 * Build (GCC – will use the volatile fallback because of -DOPENSSL_NO_ASM):
 *   gcc -DOPENSSL_NO_ASM -std=c11 -o test_constant_time test_constant_time.c
 *
 * Build (GCC – ASM path, tests that the asm variant also passes):
 *   gcc -std=c11 -o test_constant_time test_constant_time.c
 */

#include <stdint.h>
#include "test.h"

/* ------------------------------------------------------------------ */
/* Minimal compatibility shims                                          */
/* ------------------------------------------------------------------ */

/* chibicc does not define ossl_inline; map it to nothing / static. */
#ifndef ossl_inline
#define ossl_inline
#endif

/* ------------------------------------------------------------------ */
/* Functions under test (copied verbatim from the original header)     */
/* ------------------------------------------------------------------ */

static ossl_inline unsigned int value_barrier(unsigned int a)
{
#if !defined(OPENSSL_NO_ASM) && defined(__GNUC__)
    unsigned int r;
    __asm__("" : "=r"(r) : "0"(a));
#else
    volatile unsigned int r = a;
#endif
    return r;
}

static ossl_inline uint32_t value_barrier_32(uint32_t a)
{
#if !defined(OPENSSL_NO_ASM) && defined(__GNUC__)
    uint32_t r;
    __asm__("" : "=r"(r) : "0"(a));
#else
    volatile uint32_t r = a;
#endif
    return r;
}

static ossl_inline uint64_t value_barrier_64(uint64_t a)
{
#if !defined(OPENSSL_NO_ASM) && defined(__GNUC__)
    uint64_t r;
    __asm__("" : "=r"(r) : "0"(a));
#else
    volatile uint64_t r = a;
#endif
    return r;
}

/*
 * constant_time_cond_swap_32
 * mask must be 0xFFFFFFFF (swap) or 0x00000000 (no-op).
 */
static ossl_inline void constant_time_cond_swap_32(uint32_t mask,
                                                    uint32_t *a,
                                                    uint32_t *b)
{
    uint32_t xorval = *a ^ *b;
    xorval &= value_barrier_32(mask);
    *a ^= xorval;
    *b ^= xorval;
}

/*
 * constant_time_cond_swap_64
 * mask must be 0xFFFFFFFFFFFFFFFF (swap) or 0x00000000 (no-op).
 */
static ossl_inline void constant_time_cond_swap_64(uint64_t mask,
                                                    uint64_t *a,
                                                    uint64_t *b)
{
    uint64_t xorval = *a ^ *b;
    xorval &= value_barrier_64(mask);
    *a ^= xorval;
    *b ^= xorval;
}

/* ------------------------------------------------------------------ */
/* Tiny test framework (no external deps)                              */
/* ------------------------------------------------------------------ */

static int g_pass = 0;
static int g_fail = 0;

/* Integer equality check */
#define CHECK_EQ(label, got, expected)                                    \
    do {                                                                   \
        if ((got) == (expected)) {                                         \
            printf("  PASS  %s\n", label);                                 \
            g_pass++;                                                      \
        } else {                                                           \
            printf("  FAIL  %s : got 0x%llx, expected 0x%llx\n",          \
                   label,                                                  \
                   (unsigned long long)(got),                              \
                   (unsigned long long)(expected));                        \
            g_fail++;                                                      \
        }                                                                  \
    } while (0)

/* ------------------------------------------------------------------ */
/* Test: value_barrier (unsigned int)                                   */
/* ------------------------------------------------------------------ */

static void test_value_barrier_uint(void)
{
    printf("\n[value_barrier – unsigned int]\n");

    CHECK_EQ("zero passthrough",      value_barrier(0u),          0u);
    CHECK_EQ("one passthrough",       value_barrier(1u),          1u);
    CHECK_EQ("max passthrough",       value_barrier(0xFFFFFFFFu), 0xFFFFFFFFu);
    CHECK_EQ("midrange passthrough",  value_barrier(0xDEADBEEFu), 0xDEADBEEFu);
    CHECK_EQ("alternating bits hi",   value_barrier(0xAAAAAAAAu), 0xAAAAAAAAu);
    CHECK_EQ("alternating bits lo",   value_barrier(0x55555555u), 0x55555555u);
}

/* ------------------------------------------------------------------ */
/* Test: value_barrier_32                                               */
/* ------------------------------------------------------------------ */

static void test_value_barrier_32(void)
{
    printf("\n[value_barrier_32 – uint32_t]\n");

    CHECK_EQ("zero",        value_barrier_32(0),           (uint32_t)0);
    CHECK_EQ("one",         value_barrier_32(1),           (uint32_t)1);
    CHECK_EQ("all-ones",    value_barrier_32(0xFFFFFFFFu), (uint32_t)0xFFFFFFFFu);
    CHECK_EQ("0xCAFEBABE",  value_barrier_32(0xCAFEBABEu), (uint32_t)0xCAFEBABEu);
    CHECK_EQ("0x00000001",  value_barrier_32(1u),          (uint32_t)1u);
    CHECK_EQ("0x80000000",  value_barrier_32(0x80000000u), (uint32_t)0x80000000u);
}

/* ------------------------------------------------------------------ */
/* Test: value_barrier_64                                               */
/* ------------------------------------------------------------------ */

static void test_value_barrier_64(void)
{
    printf("\n[value_barrier_64 – uint64_t]\n");

    CHECK_EQ("zero",
             value_barrier_64(0),
             (uint64_t)0);
    CHECK_EQ("one",
             value_barrier_64(1),
             (uint64_t)1);
    CHECK_EQ("all-ones",
             value_barrier_64(UINT64_C(0xFFFFFFFFFFFFFFFF)),
             UINT64_C(0xFFFFFFFFFFFFFFFF));
    CHECK_EQ("high-word only",
             value_barrier_64(UINT64_C(0xDEADBEEF00000000)),
             UINT64_C(0xDEADBEEF00000000));
    CHECK_EQ("low-word only",
             value_barrier_64(UINT64_C(0x00000000CAFEBABE)),
             UINT64_C(0x00000000CAFEBABE));
    CHECK_EQ("alternating 64-bit",
             value_barrier_64(UINT64_C(0xAAAAAAAAAAAAAAAA)),
             UINT64_C(0xAAAAAAAAAAAAAAAA));
}

/* ------------------------------------------------------------------ */
/* Test: constant_time_cond_swap_32                                     */
/* ------------------------------------------------------------------ */

static void test_cond_swap_32(void)
{
    uint32_t a, b;
    printf("\n[constant_time_cond_swap_32]\n");

    /* --- mask = 0xFFFFFFFF : must swap --- */
    a = 0xAAAAAAAAu;  b = 0x55555555u;
    constant_time_cond_swap_32(0xFFFFFFFFu, &a, &b);
    CHECK_EQ("swap mask=FF: a becomes 0x55555555", a, (uint32_t)0x55555555u);
    CHECK_EQ("swap mask=FF: b becomes 0xAAAAAAAA", b, (uint32_t)0xAAAAAAAAu);

    /* --- mask = 0x00000000 : must NOT swap --- */
    a = 0xAAAAAAAAu;  b = 0x55555555u;
    constant_time_cond_swap_32(0x00000000u, &a, &b);
    CHECK_EQ("noop mask=00: a unchanged",  a, (uint32_t)0xAAAAAAAAu);
    CHECK_EQ("noop mask=00: b unchanged",  b, (uint32_t)0x55555555u);

    /* --- both values equal, swap mask --- */
    a = 0x12345678u;  b = 0x12345678u;
    constant_time_cond_swap_32(0xFFFFFFFFu, &a, &b);
    CHECK_EQ("equal values swap: a unchanged", a, (uint32_t)0x12345678u);
    CHECK_EQ("equal values swap: b unchanged", b, (uint32_t)0x12345678u);

    /* --- both values equal, noop mask --- */
    a = 0xDEADBEEFu;  b = 0xDEADBEEFu;
    constant_time_cond_swap_32(0x00000000u, &a, &b);
    CHECK_EQ("equal values noop: a unchanged", a, (uint32_t)0xDEADBEEFu);
    CHECK_EQ("equal values noop: b unchanged", b, (uint32_t)0xDEADBEEFu);

    /* --- boundary: a=0 b=MAX, swap --- */
    a = 0u;  b = 0xFFFFFFFFu;
    constant_time_cond_swap_32(0xFFFFFFFFu, &a, &b);
    CHECK_EQ("0<->MAX swap: a becomes MAX", a, (uint32_t)0xFFFFFFFFu);
    CHECK_EQ("0<->MAX swap: b becomes 0",  b, (uint32_t)0u);

    /* --- boundary: a=0 b=MAX, noop --- */
    a = 0u;  b = 0xFFFFFFFFu;
    constant_time_cond_swap_32(0x00000000u, &a, &b);
    CHECK_EQ("0<->MAX noop: a stays 0",   a, (uint32_t)0u);
    CHECK_EQ("0<->MAX noop: b stays MAX", b, (uint32_t)0xFFFFFFFFu);

    /* --- idempotency: double swap restores originals --- */
    a = 0xCAFEBABEu;  b = 0x0FF1CE00u;
    constant_time_cond_swap_32(0xFFFFFFFFu, &a, &b);
    constant_time_cond_swap_32(0xFFFFFFFFu, &a, &b);
    CHECK_EQ("double swap: a restored", a, (uint32_t)0xCAFEBABEu);
    CHECK_EQ("double swap: b restored", b, (uint32_t)0x0FF1CE00u);
}

/* ------------------------------------------------------------------ */
/* Test: constant_time_cond_swap_64                                     */
/* ------------------------------------------------------------------ */

static void test_cond_swap_64(void)
{
    uint64_t a, b;
    printf("\n[constant_time_cond_swap_64]\n");

    /* --- mask = all-ones : must swap --- */
    a = UINT64_C(0xAAAAAAAAAAAAAAAA);
    b = UINT64_C(0x5555555555555555);
    constant_time_cond_swap_64(UINT64_C(0xFFFFFFFFFFFFFFFF), &a, &b);
    CHECK_EQ("swap mask=FF: a becomes 0x5555...", a, UINT64_C(0x5555555555555555));
    CHECK_EQ("swap mask=FF: b becomes 0xAAAA...", b, UINT64_C(0xAAAAAAAAAAAAAAAA));

    /* --- mask = 0 : must NOT swap --- */
    a = UINT64_C(0xAAAAAAAAAAAAAAAA);
    b = UINT64_C(0x5555555555555555);
    constant_time_cond_swap_64(UINT64_C(0), &a, &b);
    CHECK_EQ("noop mask=00: a unchanged", a, UINT64_C(0xAAAAAAAAAAAAAAAA));
    CHECK_EQ("noop mask=00: b unchanged", b, UINT64_C(0x5555555555555555));

    /* --- equal values, swap mask --- */
    a = UINT64_C(0x0123456789ABCDEF);
    b = UINT64_C(0x0123456789ABCDEF);
    constant_time_cond_swap_64(UINT64_C(0xFFFFFFFFFFFFFFFF), &a, &b);
    CHECK_EQ("equal values swap: a unchanged", a, UINT64_C(0x0123456789ABCDEF));
    CHECK_EQ("equal values swap: b unchanged", b, UINT64_C(0x0123456789ABCDEF));

    /* --- boundary: a=0 b=MAX, swap --- */
    a = UINT64_C(0);
    b = UINT64_C(0xFFFFFFFFFFFFFFFF);
    constant_time_cond_swap_64(UINT64_C(0xFFFFFFFFFFFFFFFF), &a, &b);
    CHECK_EQ("0<->MAX swap: a becomes MAX", a, UINT64_C(0xFFFFFFFFFFFFFFFF));
    CHECK_EQ("0<->MAX swap: b becomes 0",  b, UINT64_C(0));

    /* --- boundary: a=0 b=MAX, noop --- */
    a = UINT64_C(0);
    b = UINT64_C(0xFFFFFFFFFFFFFFFF);
    constant_time_cond_swap_64(UINT64_C(0), &a, &b);
    CHECK_EQ("0<->MAX noop: a stays 0",   a, UINT64_C(0));
    CHECK_EQ("0<->MAX noop: b stays MAX", b, UINT64_C(0xFFFFFFFFFFFFFFFF));

    /* --- high-word only differs --- */
    a = UINT64_C(0xDEADBEEF00000000);
    b = UINT64_C(0xCAFEBABE00000000);
    constant_time_cond_swap_64(UINT64_C(0xFFFFFFFFFFFFFFFF), &a, &b);
    CHECK_EQ("high-word swap: a", a, UINT64_C(0xCAFEBABE00000000));
    CHECK_EQ("high-word swap: b", b, UINT64_C(0xDEADBEEF00000000));

    /* --- idempotency: double swap restores originals --- */
    a = UINT64_C(0x0000000100000002);
    b = UINT64_C(0xFFFFFFFEFFFFFFFD);
    constant_time_cond_swap_64(UINT64_C(0xFFFFFFFFFFFFFFFF), &a, &b);
    constant_time_cond_swap_64(UINT64_C(0xFFFFFFFFFFFFFFFF), &a, &b);
    CHECK_EQ("double swap: a restored", a, UINT64_C(0x0000000100000002));
    CHECK_EQ("double swap: b restored", b, UINT64_C(0xFFFFFFFEFFFFFFFD));
}

/* ------------------------------------------------------------------ */
/* main                                                                 */
/* ------------------------------------------------------------------ */

int main(void)
{
    printf("=== constant-time helpers – chibicc test suite ===\n");

    test_value_barrier_uint();
    test_value_barrier_32();
    test_value_barrier_64();
    test_cond_swap_32();
    test_cond_swap_64();

    printf("\n=== Results: %d passed, %d failed ===\n", g_pass, g_fail);
    return g_fail == 0 ? 0 : 1;
}
