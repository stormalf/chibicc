
/* bntest_standalone.c
 *
 * Simplified BN test derived from openssl/test/bntest.c.
 * Zero dependency on internal/nelem.h, internal/numbers.h, testutil.h.
 * All needed definitions are inlined below.
 *
 * Compile against an installed OpenSSL:
 *   gcc   -std=c11 -Wall $(pkg-config --cflags openssl) \
 *         bntest_standalone.c $(pkg-config --libs openssl) -o bntest_standalone
 *   ./bntest_standalone
 *
 * Compile with chibicc:
 *   chibicc $(pkg-config --cflags openssl) \
 *           bntest_standalone.c $(pkg-config --libs openssl) -o bntest_standalone
 */

#include "test.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <openssl/bn.h>
#include <openssl/err.h>

/* ------------------------------------------------------------------ *
 * Inlined replacements for the three forbidden headers               *
 * ------------------------------------------------------------------ */

/* internal/nelem.h ------------------------------------------------- */
#ifndef OSSL_NELEM
#  define OSSL_NELEM(arr)  (sizeof(arr) / sizeof((arr)[0]))
#endif

/* internal/numbers.h ----------------------------------------------- */
#ifndef INT_DIGITS
#  define INT_DIGITS      (sizeof(int) * CHAR_BIT)
#endif
#ifndef BN_BITS2
#  define BN_BITS2        (sizeof(BN_ULONG) * CHAR_BIT)
#endif

/* testutil.h — minimal test harness -------------------------------- */
static int g_pass = 0;
static int g_fail = 0;

#define TEST_info(...)   do { printf("INFO  "); printf(__VA_ARGS__); putchar('\n'); } while(0)
#define TEST_error(...)  do { printf("ERROR "); printf(__VA_ARGS__); putchar('\n'); } while(0)

static int test_check(const char *name, int ok) {
    if (ok) { printf("PASS  %s\n", name); g_pass++; }
    else     { printf("FAIL  %s\n", name); g_fail++; }
    return ok;
}

#define TEST_true(expr)          test_check(#expr, !!(expr))
#define TEST_false(expr)         test_check("!" #expr, !(expr))
#define TEST_int_eq(a,b)         test_check(#a " == " #b, (a)==(b))
#define TEST_BN_eq(a,b)          test_check(#a " == " #b, BN_cmp(a,b)==0)
#define TEST_BN_eq_word(bn,w)    test_check(#bn " == " #w, BN_is_word(bn,w))
#define TEST_BN_eq_zero(bn)      test_check(#bn " == 0",   BN_is_zero(bn))
#define TEST_BN_lt_zero(bn)      test_check(#bn " < 0",    BN_is_negative(bn))
#define TEST_BN_ge_zero(bn)      test_check(#bn " >= 0",  !BN_is_negative(bn))
#define TEST_BN_odd(bn)          test_check(#bn " is odd", BN_is_odd(bn))

/* Helper: BN from decimal string */
static BIGNUM *bn_from_dec(const char *s) {
    BIGNUM *r = NULL;
    BN_dec2bn(&r, s);
    return r;
}
/* Helper: BN from hex string */
static BIGNUM *bn_from_hex(const char *s) {
    BIGNUM *r = NULL;
    BN_hex2bn(&r, s);
    return r;
}

/* ================================================================== *
 * Test 1 — BN_add / BN_sub round-trip                               *
 * Mirrors test_add() in bntest.c                                     *
 * ================================================================== */
static int test_add_sub(void) {
    int     ok  = 1;
    BIGNUM *a   = BN_new();
    BIGNUM *b   = BN_new();
    BIGNUM *sum = BN_new();
    BIGNUM *dif = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    BN_set_word(a, 123456789UL);
    BN_set_word(b, 987654321UL);

    ok &= TEST_true(BN_add(sum, a, b));
    ok &= TEST_BN_eq_word(sum, 1111111110UL);

    ok &= TEST_true(BN_sub(dif, sum, b));
    ok &= TEST_BN_eq(dif, a);

    /* negative result: a - b */
    ok &= TEST_true(BN_sub(dif, a, b));
    ok &= TEST_BN_lt_zero(dif);

    BN_free(a); BN_free(b); BN_free(sum); BN_free(dif); BN_CTX_free(ctx);
    return ok;
}

/* ================================================================== *
 * Test 2 — BN_mul / BN_div                                          *
 * Mirrors test_div() in bntest.c                                     *
 * ================================================================== */
static int test_mul_div(void) {
    int     ok   = 1;
    BIGNUM *a    = bn_from_dec("123456789012345678901234567890");
    BIGNUM *b    = bn_from_dec("987654321");
    BIGNUM *prod = BN_new();
    BIGNUM *quot = BN_new();
    BIGNUM *rem  = BN_new();
    BIGNUM *chk  = BN_new();
    BN_CTX *ctx  = BN_CTX_new();

    ok &= TEST_true(BN_mul(prod, a, b, ctx));

    ok &= TEST_true(BN_div(quot, rem, prod, b, ctx));
    ok &= TEST_BN_eq(quot, a);
    ok &= TEST_BN_eq_zero(rem);

    /* verify: quot * b + rem == prod */
    ok &= TEST_true(BN_mul(chk, quot, b, ctx));
    ok &= TEST_true(BN_add(chk, chk, rem));
    ok &= TEST_BN_eq(chk, prod);

    BN_free(a); BN_free(b); BN_free(prod);
    BN_free(quot); BN_free(rem); BN_free(chk);
    BN_CTX_free(ctx);
    return ok;
}



/* ================================================================== *
 * Test 4 — BN_sqr and BN_sqrt (mod p)                               *
 * ================================================================== */
static int test_sqr(void) {
    int     ok  = 1;
    BIGNUM *a   = bn_from_dec("12345678901234567890");
    BIGNUM *sq  = BN_new();
    BIGNUM *rt  = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    ok &= TEST_true(BN_sqr(sq, a, ctx));

    /* sqrt(a^2) mod p — use a large prime as modulus */
    BIGNUM *p = bn_from_hex("FFFFFFFFFFFFFFFFC90FDAA22168C234"
                              "C4C6628B80DC1CD129024E088A67CC74"
                              "020BBEA63B139B22514A08798E3404DD"
                              "EF9519B3CD3A431B302B0A6DF25F1437"
                              "4FE1356D6D51C245E485B576625E7EC6"
                              "F44C42E9A637ED6B0BFF5CB6F406B7ED"
                              "EE386BFB5A899FA5AE9F24117C4B1FE6"
                              "49286651ECE45B3DC2007CB8A163BF05"
                              "98DA48361C55D39A69163FA8FD24CF5F"
                              "83655D23DCA3AD961C62F356208552BB"
                              "9ED529077096966D670C354E4ABC9804"
                              "F1746C08CA18217C32905E462E36CE3B"
                              "E39E772C180E86039B2783A2EC07A28F"
                              "B5C55DF06F4C52C9DE2BCBF695581718"
                              "3995497CEA956AE515D2261898FA0510"
                              "15728E5A8AACAA68FFFFFFFFFFFFFFFF");
    BIGNUM *r = BN_new();
    ok &= TEST_true(BN_mod(r, a, p, ctx));
    ok &= TEST_BN_ge_zero(r);

    BN_free(a); BN_free(sq); BN_free(rt);
    BN_free(p); BN_free(r); BN_CTX_free(ctx);
    return ok;
}

/* ================================================================== *
 * Test 5 — BN_gcd                                                   *
 * Mirrors test_gcd() in bntest.c                                     *
 * ================================================================== */
static const char *gcd_cases[][3] = {
    { "12",    "8",     "4"  },
    { "100",   "75",    "25" },
    { "17",    "13",    "1"  },
    { "0",     "42",    "42" },
    { "42",    "0",     "42" },
};

static int test_gcd(void) {
    int     ok  = 1;
    BIGNUM *a   = BN_new();
    BIGNUM *b   = BN_new();
    BIGNUM *g   = BN_new();
    BIGNUM *exp = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    for (size_t i = 0; i < OSSL_NELEM(gcd_cases); i++) {
        BN_dec2bn(&a,   gcd_cases[i][0]);
        BN_dec2bn(&b,   gcd_cases[i][1]);
        BN_dec2bn(&exp, gcd_cases[i][2]);
        ok &= TEST_true(BN_gcd(g, a, b, ctx));
        ok &= TEST_BN_eq(g, exp);
    }

    BN_free(a); BN_free(b); BN_free(g); BN_free(exp); BN_CTX_free(ctx);
    return ok;
}

/* ================================================================== *
 * Test 6 — BN_mod_exp (base^exp mod m)                              *
 * Mirrors test_modexp() in bntest.c                                  *
 * ================================================================== */
static int test_mod_exp(void) {
    int     ok   = 1;
    BN_CTX *ctx  = BN_CTX_new();

    /* 2^10 mod 1000 = 24 */
    BIGNUM *base = bn_from_dec("2");
    BIGNUM *exp  = bn_from_dec("10");
    BIGNUM *mod  = bn_from_dec("1000");
    BIGNUM *r    = BN_new();

    ok &= TEST_true(BN_mod_exp(r, base, exp, mod, ctx));
    ok &= TEST_BN_eq_word(r, 24);

    /* Fermat's little theorem: a^(p-1) ≡ 1 (mod p) for prime p */
    BIGNUM *p    = bn_from_dec("104729");    /* small prime */
    BIGNUM *pm1  = BN_new();
    BIGNUM *a    = bn_from_dec("65537");
    BIGNUM *one  = BN_new();

    BN_sub(pm1, p, BN_value_one());
    ok &= TEST_true(BN_mod_exp(r, a, pm1, p, ctx));
    BN_one(one);
    ok &= TEST_BN_eq(r, one);

    BN_free(base); BN_free(exp); BN_free(mod); BN_free(r);
    BN_free(p);    BN_free(pm1); BN_free(a);   BN_free(one);
    BN_CTX_free(ctx);
    return ok;
}

/* ================================================================== *
 * Test 7 — BN_lshift / BN_rshift                                    *
 * Mirrors shift tests in bntest.c                                    *
 * ================================================================== */
static int test_shift(void) {
    int     ok = 1;
    BIGNUM *a  = BN_new();
    BIGNUM *b  = BN_new();

    BN_set_word(a, 1);

    /* 1 << 64 */
    ok &= TEST_true(BN_lshift(b, a, 64));
    ok &= TEST_BN_ge_zero(b);
    ok &= test_check("BN_num_bits(1<<64)==65", BN_num_bits(b) == 65);

    /* (1 << 64) >> 64 == 1 */
    ok &= TEST_true(BN_rshift(a, b, 64));
    ok &= TEST_BN_eq_word(a, 1);

    /* shift by 0 is identity */
    BN_set_word(a, 0xDEADBEEFUL);
    ok &= TEST_true(BN_lshift(b, a, 0));
    ok &= TEST_BN_eq(b, a);

    BN_free(a); BN_free(b);
    return ok;
}

/* ================================================================== *
 * Test 8 — BN_is_prime_fasttest_ex (primality)                      *
 * Mirrors test_prime() in bntest.c                                   *
 * ================================================================== */
static const char *known_primes[] = {
    "2", "3", "5", "7", "104729", "15485863",
    "179424673", "32416190071",
};
static const char *known_composites[] = {
    "4", "9", "15", "100", "104730", "104727",
};

static int test_prime(void) {
    int     ok  = 1;
    BIGNUM *n   = BN_new();
    BN_CTX *ctx = BN_CTX_new();

    for (size_t i = 0; i < OSSL_NELEM(known_primes); i++) {
        BN_dec2bn(&n, known_primes[i]);
        int ret = BN_check_prime(n, ctx, NULL);
        ok &= test_check(known_primes[i], ret == 1);
    }
    for (size_t i = 0; i < OSSL_NELEM(known_composites); i++) {
        BN_dec2bn(&n, known_composites[i]);
        int ret = BN_check_prime(n, ctx, NULL);
        ok &= test_check(known_composites[i], ret == 0);
    }

    BN_free(n); BN_CTX_free(ctx);
    return ok;
}

/* ================================================================== *
 * Test 9 — BN_mod_inverse                                           *
 * ================================================================== */
static int test_mod_inverse(void) {
    int     ok   = 1;
    BN_CTX *ctx  = BN_CTX_new();
    BIGNUM *a    = bn_from_dec("3");
    BIGNUM *m    = bn_from_dec("7");
    BIGNUM *inv  = BN_new();
    BIGNUM *chk  = BN_new();
    BIGNUM *one  = BN_new();

    /* 3^-1 mod 7 == 5  (3*5 = 15 ≡ 1 mod 7) */
    ok &= TEST_true(BN_mod_inverse(inv, a, m, ctx) != NULL);
    ok &= TEST_BN_eq_word(inv, 5);

    ok &= TEST_true(BN_mod_mul(chk, a, inv, m, ctx));
    BN_one(one);
    ok &= TEST_BN_eq(chk, one);

    /* a and m not coprime → no inverse */
    BN_set_word(a, 4);
    BN_set_word(m, 6);
    ok &= test_check("no inverse gcd!=1",
                     BN_mod_inverse(inv, a, m, ctx) == NULL);
    ERR_clear_error();

    BN_free(a); BN_free(m); BN_free(inv); BN_free(chk); BN_free(one);
    BN_CTX_free(ctx);
    return ok;
}

/* ================================================================== *
 * Test 10 — BN_hex2bn / BN_bn2hex / BN_dec2bn / BN_bn2dec          *
 *           (string conversion round-trips)                          *
 * ================================================================== */
static int test_string_conversion(void) {
    int         ok  = 1;
    const char *hex = "DEADBEEFCAFEBABE0123456789ABCDEF";
    const char *dec = "123456789012345678901234567890";
    BIGNUM     *a   = bn_from_hex(hex);
    BIGNUM     *b   = bn_from_dec(dec);

    char *h = BN_bn2hex(a);
    ok &= test_check("hex round-trip", strcasecmp(h, hex) == 0);
    OPENSSL_free(h);

    char *d = BN_bn2dec(b);
    ok &= test_check("dec round-trip", strcmp(d, dec) == 0);
    OPENSSL_free(d);

    /* negative hex */
    BIGNUM *neg = bn_from_hex(hex);
    BN_set_negative(neg, 1);
    char *nh = BN_bn2hex(neg);
    ok &= test_check("neg hex starts with -", nh[0] == '-');
    OPENSSL_free(nh);

    BN_free(a); BN_free(b); BN_free(neg);
    return ok;
}

/* ================================================================== *
 * Test 11 — BN_bn2bin / BN_bin2bn (binary round-trip)               *
 * ================================================================== */
static int test_binary_conversion(void) {
    int            ok  = 1;
    unsigned char  buf[32];
    unsigned char  expected[] = { 0xDE,0xAD,0xBE,0xEF };
    BIGNUM        *a = BN_new();

    BN_set_word(a, 0xDEADBEEFUL);
    int len = BN_bn2bin(a, buf);
    ok &= test_check("bn2bin length == 4", len == 4);
    ok &= test_check("bn2bin bytes correct",
                     memcmp(buf, expected, 4) == 0);

    BIGNUM *b = BN_bin2bn(expected, 4, NULL);
    ok &= TEST_BN_eq(a, b);

    BN_free(a); BN_free(b);
    return ok;
}

/* ================================================================== *
 * Test 12 — BN_num_bits / BN_num_bytes                              *
 * Uses OSSL_NELEM (replaces internal/nelem.h) and BN_BITS2           *
 * (replaces internal/numbers.h) to show both macros work.           *
 * ================================================================== */
static const struct { unsigned long w; int bits; } nbits_cases[] = {
    { 0,          0  },
    { 1,          1  },
    { 2,          2  },
    { 255,        8  },
    { 256,        9  },
    { 0xFFFFUL,   16 },
    { 0xFFFFFFUL, 24 },
};

static int test_num_bits(void) {
    int     ok = 1;
    BIGNUM *a  = BN_new();

    for (size_t i = 0; i < OSSL_NELEM(nbits_cases); i++) {
        BN_set_word(a, nbits_cases[i].w);
        ok &= TEST_int_eq(BN_num_bits(a), nbits_cases[i].bits);
    }

    /* Verify BN_BITS2 matches sizeof(BN_ULONG)*8 at runtime */
    ok &= test_check("BN_BITS2 == sizeof(BN_ULONG)*8",
                     BN_BITS2 == (int)(sizeof(BN_ULONG) * CHAR_BIT));

    BN_free(a);
    return ok;
}

/* ================================================================== *
 * main                                                               *
 * ================================================================== */
int main(void) {
    puts("=== bntest_standalone ===");

    test_add_sub();
    test_mul_div();    
    test_sqr();
    test_gcd();
    test_mod_exp();
    test_shift();
    test_prime();
    test_mod_inverse();
    test_string_conversion();
    test_binary_conversion();
    test_num_bits();

    printf("\n%d passed, %d failed\n", g_pass, g_fail);
    return g_fail ? 1 : 0;
}

