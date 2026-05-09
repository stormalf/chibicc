/*
 * test_bignum_chibicc.c
 * Comprehensive BIGNUM test suite for validating chibicc compiler compatibility.
 * Covers: arithmetic, modular ops, bitwise ops, comparison, I/O, primes,
 *         memory, edge cases (zero, one, negatives, overflow-prone values).
 *
 * Build:  cc test_bignum_chibicc.c -o test_bignum -lssl -lcrypto
 * Run:    ./test_bignum
 */

#include <openssl/bn.h>
#include <openssl/rand.h>
#include "test.h"
#include <string.h>

/* ── helpers ───────────────────────────────────────────────────────────── */

static int tests_run    = 0;
static int tests_passed = 0;
static int tests_failed = 0;

#define PASS(label) do { \
    printf("[PASS] %s\n", label); \
    tests_passed++; tests_run++; \
} while (0)

#define FAIL(label) do { \
    printf("[FAIL] %s\n", label); \
    tests_failed++; tests_run++; \
} while (0)

#define CHECK(cond, label) do { \
    if (cond) PASS(label); else FAIL(label); \
} while (0)

/* ── 1. Memory / lifecycle ─────────────────────────────────────────────── */
static void test_memory(void)
{
    puts("\n=== 1. Memory / Lifecycle ===");

    /* BN_new / BN_free */
    BIGNUM *a = BN_new();
    CHECK(a != NULL, "BN_new returns non-NULL");
    BN_free(a);

    /* BN_clear_free (secure wipe) */
    BIGNUM *b = BN_new();
    BN_set_word(b, 0xDEADBEEF);
    BN_clear_free(b);                       /* should not crash */
    PASS("BN_clear_free does not crash");

    /* BN_dup */
    BIGNUM *src = BN_new();
    BN_set_word(src, 123456789UL);
    BIGNUM *dup = BN_dup(src);
    CHECK(BN_cmp(src, dup) == 0, "BN_dup produces equal value");
    BN_free(src); BN_free(dup);

    /* BN_copy */
    BIGNUM *x = BN_new(); BIGNUM *y = BN_new();
    BN_set_word(x, 42);
    BN_copy(y, x);
    CHECK(BN_cmp(x, y) == 0, "BN_copy produces equal value");
    BN_free(x); BN_free(y);

    /* BN_CTX lifecycle */
    BN_CTX *ctx = BN_CTX_new();
    CHECK(ctx != NULL, "BN_CTX_new returns non-NULL");
    BN_CTX_free(ctx);

    /* BN_CTX_start / BN_CTX_end scoping */
    ctx = BN_CTX_new();
    BN_CTX_start(ctx);
    BIGNUM *tmp = BN_CTX_get(ctx);
    CHECK(tmp != NULL, "BN_CTX_get inside start/end");
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
}

/* ── 2. Initialisation & conversion ────────────────────────────────────── */
static void test_conversion(void)
{
    puts("\n=== 2. Initialisation & Conversion ===");

    BIGNUM *a = BN_new();

    /* zero / one constants */
    BN_zero(a); CHECK(BN_is_zero(a), "BN_zero / BN_is_zero");
    BN_one(a);  CHECK(BN_is_one(a),  "BN_one  / BN_is_one");

    /* set_word / get_word round-trip */
    BN_set_word(a, 0xCAFEBABEUL);
    CHECK(BN_get_word(a) == 0xCAFEBABEUL, "BN_set/get_word round-trip");

    /* hex string round-trip */
    BN_hex2bn(&a, "DEADBEEFCAFE1234");
    char *hex = BN_bn2hex(a);
    CHECK(strcasecmp(hex, "DEADBEEFCAFE1234") == 0, "hex2bn / bn2hex round-trip");
    OPENSSL_free(hex);

    /* decimal string round-trip */
    BN_dec2bn(&a, "123456789012345678901234567890");
    char *dec = BN_bn2dec(a);
    CHECK(strcmp(dec, "123456789012345678901234567890") == 0, "dec2bn / bn2dec round-trip");
    OPENSSL_free(dec);

    /* binary round-trip */
    BN_set_word(a, 0xABCD);
    int len = BN_num_bytes(a);
    unsigned char buf[64];
    BN_bn2bin(a, buf);
    BIGNUM *b = BN_new();
    BN_bin2bn(buf, len, b);
    CHECK(BN_cmp(a, b) == 0, "bn2bin / bin2bn round-trip");
    BN_free(b);

    /* BN_num_bits */
    BN_set_word(a, 8);   /* 0b1000 → 4 bits */
    CHECK(BN_num_bits(a) == 4, "BN_num_bits(8) == 4");

    BN_free(a);
}

/* ── 3. Arithmetic ─────────────────────────────────────────────────────── */
static void test_arithmetic(BN_CTX *ctx)
{
    puts("\n=== 3. Arithmetic ===");

    BIGNUM *a = BN_new(), *b = BN_new(), *r = BN_new();

    /* addition */
    BN_set_word(a, 999999999UL);
    BN_set_word(b, 1UL);
    BN_add(r, a, b);
    CHECK(BN_get_word(r) == 1000000000UL, "BN_add: 999999999+1=1000000000");

    /* subtraction */
    BN_set_word(a, 100); BN_set_word(b, 37);
    BN_sub(r, a, b);
    CHECK(BN_get_word(r) == 63, "BN_sub: 100-37=63");

    /* multiplication */
    BN_set_word(a, 123456); BN_set_word(b, 789);
    BN_mul(r, a, b, ctx);
    CHECK(BN_get_word(r) == 123456UL * 789UL, "BN_mul: 123456*789");

    /* squaring */
    BN_set_word(a, 1234);
    BN_sqr(r, a, ctx);
    CHECK(BN_get_word(r) == 1234UL * 1234UL, "BN_sqr: 1234^2");

    /* division + remainder */
    BIGNUM *q = BN_new(), *rem = BN_new();
    BN_set_word(a, 1000); BN_set_word(b, 7);
    BN_div(q, rem, a, b, ctx);
    CHECK(BN_get_word(q) == 142 && BN_get_word(rem) == 6, "BN_div: 1000/7 q=142 r=6");
    BN_free(q); BN_free(rem);

    /* BN_add_word / BN_sub_word / BN_mul_word */
    BN_set_word(a, 500);
    BN_add_word(a, 23);  CHECK(BN_get_word(a) == 523,  "BN_add_word");
    BN_sub_word(a, 3);   CHECK(BN_get_word(a) == 520,  "BN_sub_word");
    BN_mul_word(a, 2);   CHECK(BN_get_word(a) == 1040, "BN_mul_word");

    /* absolute value (negate then abs) */
    BN_set_word(a, 42); BN_set_negative(a, 1);
    CHECK(BN_is_negative(a), "BN_set_negative makes number negative");
    BN_set_negative(a, 0);
    CHECK(!BN_is_negative(a), "BN_set_negative(0) clears sign");

    BN_free(a); BN_free(b); BN_free(r);
}

/* ── 4. Modular arithmetic ─────────────────────────────────────────────── */
static void test_modular(BN_CTX *ctx)
{
    puts("\n=== 4. Modular Arithmetic ===");

    BIGNUM *a = BN_new(), *m = BN_new(), *r = BN_new();
    BIGNUM *e = BN_new();

    /* BN_mod */
    BN_set_word(a, 1234567); BN_set_word(m, 1000);
    BN_mod(r, a, m, ctx);
    CHECK(BN_get_word(r) == 567, "BN_mod: 1234567 mod 1000 = 567");

    /* BN_mod_add */
    BN_set_word(a, 999); BN_set_word(e, 5); BN_set_word(m, 1000);
    BN_mod_add(r, a, e, m, ctx);
    CHECK(BN_get_word(r) == 4, "BN_mod_add: (999+5) mod 1000 = 4");

    /* BN_mod_sub */
    BN_set_word(a, 3); BN_set_word(e, 7); BN_set_word(m, 10);
    BN_mod_sub(r, a, e, m, ctx);
    CHECK(BN_get_word(r) == 6, "BN_mod_sub: (3-7) mod 10 = 6");

    /* BN_mod_mul */
    BN_set_word(a, 17); BN_set_word(e, 13); BN_set_word(m, 100);
    BN_mod_mul(r, a, e, m, ctx);
    CHECK(BN_get_word(r) == 21, "BN_mod_mul: (17*13) mod 100 = 21");

    /* BN_mod_sqr */
    BN_set_word(a, 17); BN_set_word(m, 100);
    BN_mod_sqr(r, a, m, ctx);
    CHECK(BN_get_word(r) == 89, "BN_mod_sqr: 17^2 mod 100 = 89");

    /* BN_mod_exp */
    BN_set_word(a, 2); BN_set_word(e, 10); BN_set_word(m, 1000);
    BN_mod_exp(r, a, e, m, ctx);
    CHECK(BN_get_word(r) == 24, "BN_mod_exp: 2^10 mod 1000 = 24");

    /* BN_mod_inverse — original example (a=17, n=3120) */
    BN_set_word(a, 17); BN_set_word(m, 3120);
    BIGNUM *inv = BN_mod_inverse(NULL, a, m, ctx);
    CHECK(inv != NULL, "BN_mod_inverse(17, 3120) succeeds");
    if (inv) {
        /* verify: a * inv ≡ 1 (mod n) */
        BN_mod_mul(r, a, inv, m, ctx);
        CHECK(BN_is_one(r), "BN_mod_inverse verification: 17 * inv ≡ 1 (mod 3120)");
        BN_free(inv);
    }

    /* BN_mod_inverse — no inverse (gcd != 1) */
    BN_set_word(a, 6); BN_set_word(m, 9);
    BIGNUM *no_inv = BN_mod_inverse(NULL, a, m, ctx);
    CHECK(no_inv == NULL, "BN_mod_inverse(6,9) returns NULL (gcd=3≠1)");

    /* BN_nnmod (non-negative modulo) */
    BIGNUM *neg = BN_new();
    BN_set_word(neg, 3); BN_set_negative(neg, 1); /* neg = -3 */
    BN_set_word(m, 7);
    BN_nnmod(r, neg, m, ctx);
    CHECK(BN_get_word(r) == 4, "BN_nnmod: -3 mod 7 = 4");
    BN_free(neg);

    /* Montgomery form round-trip */
    BN_set_word(m, 97);   /* prime modulus */
    BN_MONT_CTX *mont = BN_MONT_CTX_new();
    BN_MONT_CTX_set(mont, m, ctx);
    BN_set_word(a, 42);
    BIGNUM *am = BN_new();
    BN_to_montgomery(am, a, mont, ctx);
    BN_from_montgomery(r, am, mont, ctx);
    CHECK(BN_cmp(r, a) == 0, "Montgomery round-trip: to→from gives original value");
    BN_MONT_CTX_free(mont);
    BN_free(am);

    BN_free(a); BN_free(m); BN_free(r); BN_free(e);
}

/* ── 5. Bitwise & shift operations ─────────────────────────────────────── */
static void test_bitwise(void)
{
    puts("\n=== 5. Bitwise & Shift ===");

    BIGNUM *a = BN_new(), *r = BN_new();

    /* left / right shift */
    BN_set_word(a, 1);
    BN_lshift(r, a, 10);
    CHECK(BN_get_word(r) == 1024, "BN_lshift(1, 10) = 1024");
    BN_rshift(r, r, 10);
    CHECK(BN_get_word(r) == 1,    "BN_rshift(1024, 10) = 1");

    /* lshift1 / rshift1 */
    BN_set_word(a, 7);
    BN_lshift1(r, a); CHECK(BN_get_word(r) == 14, "BN_lshift1(7)=14");
    BN_rshift1(r, r); CHECK(BN_get_word(r) == 7,  "BN_rshift1(14)=7");

    /* BN_set_bit / BN_clear_bit / BN_is_bit_set */
    BN_zero(a);
    BN_set_bit(a, 5);
    CHECK(BN_is_bit_set(a, 5), "BN_set_bit / BN_is_bit_set(5)");
    CHECK(!BN_is_bit_set(a, 4), "bit 4 not set");
    BN_clear_bit(a, 5);
    CHECK(!BN_is_bit_set(a, 5), "BN_clear_bit(5)");

    /* BN_mask_bits */
    BN_set_word(a, 0xFF);
    BN_mask_bits(a, 4);          /* keep only lowest 4 bits → 0x0F */
    CHECK(BN_get_word(a) == 0x0F, "BN_mask_bits(0xFF, 4) = 0x0F");

    BN_free(a); BN_free(r);
}

/* ── 6. Comparison ─────────────────────────────────────────────────────── */
static void test_comparison(void)
{
    puts("\n=== 6. Comparison ===");

    BIGNUM *a = BN_new(), *b = BN_new();

    BN_set_word(a, 100); BN_set_word(b, 200);
    CHECK(BN_cmp(a, b) < 0,  "BN_cmp: 100 < 200");
    CHECK(BN_cmp(b, a) > 0,  "BN_cmp: 200 > 100");

    BN_set_word(b, 100);
    CHECK(BN_cmp(a, b) == 0, "BN_cmp: 100 == 100");

    /* BN_ucmp ignores sign */
    BN_set_negative(a, 1);
    CHECK(BN_ucmp(a, b) == 0, "BN_ucmp ignores sign: |-100| == 100");

    /* BN_cmp_word (if available via macro) */
    BN_set_word(a, 42); BN_set_negative(a, 0);
    CHECK(BN_is_zero(a) == 0, "BN_is_zero(42) == 0");
    BN_zero(a);
    CHECK(BN_is_zero(a) == 1, "BN_is_zero(0) == 1");

    CHECK(BN_is_one(b)  == 0, "BN_is_one(100) == 0");
    BN_one(b);
    CHECK(BN_is_one(b)  == 1, "BN_is_one(1) == 1");

    /* odd/even */
    BN_set_word(a, 7);
    CHECK(BN_is_odd(a),  "BN_is_odd(7)");
    BN_set_word(a, 8);
    CHECK(!BN_is_odd(a), "!BN_is_odd(8)");

    BN_free(a); BN_free(b);
}

/* ── 7. GCD & prime utilities ──────────────────────────────────────────── */
static void test_gcd_prime(BN_CTX *ctx)
{
    puts("\n=== 7. GCD & Primes ===");

    BIGNUM *a = BN_new(), *b = BN_new(), *g = BN_new();

    /* GCD */
    BN_set_word(a, 48); BN_set_word(b, 18);
    BN_gcd(g, a, b, ctx);
    CHECK(BN_get_word(g) == 6, "BN_gcd(48,18) = 6");

    BN_set_word(a, 7); BN_set_word(b, 13);
    BN_gcd(g, a, b, ctx);
    CHECK(BN_get_word(g) == 1, "BN_gcd(7,13) = 1 (coprime)");

    /* BN_is_prime_fasttest_ex */
    BN_set_word(a, 104729);   /* known prime */
    int is_prime = BN_check_prime(a, ctx, NULL);
    CHECK(is_prime == 1, "BN_check_prime(104729) is prime");

    BN_set_word(a, 104728);   /* composite */
    is_prime = BN_check_prime(a, ctx, NULL);
    CHECK(is_prime == 0, "BN_check_prime(104728) is NOT prime");

    /* BN_generate_prime_ex — small 32-bit prime */
    BIGNUM *p = BN_new();
    int ok = BN_generate_prime_ex(p, 32, 0, NULL, NULL, NULL);
    CHECK(ok == 1, "BN_generate_prime_ex(32 bits) succeeds");
    CHECK(BN_num_bits(p) <= 32, "generated prime fits in 32 bits");
    int prime_check = BN_check_prime(p, ctx, NULL);
    CHECK(prime_check == 1, "generated prime passes primality test");
    BN_free(p);

    /* safe prime (p, where (p-1)/2 is also prime) — small so fast */
    BIGNUM *sp = BN_new();
    ok = BN_generate_prime_ex(sp, 32, 1, NULL, NULL, NULL);
    CHECK(ok == 1, "BN_generate_prime_ex safe prime succeeds");
    BN_free(sp);

    BN_free(a); BN_free(b); BN_free(g);
}

/* ── 8. Pseudo-random generation ───────────────────────────────────────── */
static void test_random(BN_CTX *ctx)
{
    puts("\n=== 8. Pseudo-Random Generation ===");
    (void)ctx;

    BIGNUM *r = BN_new();

    /* BN_rand: exactly N bits, top bit set, odd */
    int ok = BN_rand(r, 64, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ODD);
    CHECK(ok == 1, "BN_rand(64 bits) succeeds");
    CHECK(BN_num_bits(r) == 64, "BN_rand produces exactly 64 bits");
    CHECK(BN_is_odd(r), "BN_rand with BN_RAND_BOTTOM_ODD is odd");

    /* BN_rand_range: result in [0, range) */
    BIGNUM *range = BN_new();
    BN_set_word(range, 1000);
    ok = BN_rand_range(r, range);
    CHECK(ok == 1, "BN_rand_range succeeds");
    CHECK(BN_cmp(r, range) < 0, "BN_rand_range result < range");

    /* BN_priv_rand_range (same semantics, uses private PRNG) */
    ok = BN_priv_rand_range(r, range);
    CHECK(ok == 1, "BN_priv_rand_range succeeds");

    BN_free(r); BN_free(range);
}

/* ── 9. Edge cases ─────────────────────────────────────────────────────── */
static void test_edge_cases(BN_CTX *ctx)
{
    puts("\n=== 9. Edge Cases ===");

    BIGNUM *a = BN_new(), *b = BN_new(), *r = BN_new();

    /* zero arithmetic */
    BN_zero(a); BN_set_word(b, 42);
    BN_add(r, a, b); CHECK(BN_get_word(r) == 42, "edge: 0 + 42 = 42");
    BN_mul(r, a, b, ctx); CHECK(BN_is_zero(r),   "edge: 0 * 42 = 0");
    BN_sub(r, a, b);      CHECK(BN_is_negative(r), "edge: 0 - 42 is negative");

    /* multiply by one */
    BN_set_word(a, 0x1234567890ABCDEFULL);
    BN_one(b);
    BN_mul(r, a, b, ctx);
    CHECK(BN_cmp(r, a) == 0, "edge: n * 1 = n");

    /* very large value (256-bit) round-trip */
    const char *big_hex =
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
        "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
    BN_hex2bn(&a, big_hex);
    char *out = BN_bn2hex(a);
    CHECK(strcasecmp(out, big_hex) == 0, "edge: 256-bit all-F round-trip");
    OPENSSL_free(out);

    /* mod by one → always 0 */
    BN_one(b);
    BN_mod(r, a, b, ctx);
    CHECK(BN_is_zero(r), "edge: n mod 1 = 0");

    /* modular exponentiation with exponent 0 → 1 */
    BN_set_word(a, 17); BN_zero(b); BN_set_word(r, 1000);
    BIGNUM *res = BN_new();
    BN_mod_exp(res, a, b, r, ctx);
    CHECK(BN_is_one(res), "edge: 17^0 mod 1000 = 1");
    BN_free(res);

    /* subtraction producing exactly zero */
    BN_set_word(a, 999); BN_set_word(b, 999);
    BN_sub(r, a, b);
    CHECK(BN_is_zero(r), "edge: n - n = 0");

    /* negative number comparison */
    BN_set_word(a, 1); BN_set_negative(a, 1);  /* a = -1 */
    BN_set_word(b, 1);                           /* b =  1 */
    CHECK(BN_cmp(a, b) < 0, "edge: -1 < 1");

    /* number of bits in zero */
    BN_zero(a);
    CHECK(BN_num_bits(a) == 0, "edge: BN_num_bits(0) = 0");
    CHECK(BN_num_bytes(a) == 0, "edge: BN_num_bytes(0) = 0");

    BN_free(a); BN_free(b); BN_free(r);
}

/* ── 10. Constant-time / secure ops ────────────────────────────────────── */
static void test_secure(BN_CTX *ctx)
{
    puts("\n=== 10. Constant-Time / Secure Ops ===");

    /* BN_mod_exp_mont_consttime */
    BIGNUM *base = BN_new(), *exp = BN_new(), *mod = BN_new(), *r = BN_new();
    BN_set_word(base, 2); BN_set_word(exp, 16); BN_set_word(mod, 65537);
    BN_mod_exp_mont_consttime(r, base, exp, mod, ctx, NULL);
    CHECK(BN_get_word(r) == 65536 % 65537, "BN_mod_exp_mont_consttime: 2^16 mod 65537");

    /* BN_priv_rand — same API as BN_rand but from private DRBG */
    BIGNUM *priv = BN_new();
    int ok = BN_priv_rand(priv, 128, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY);
    CHECK(ok == 1, "BN_priv_rand(128 bits) succeeds");
    CHECK(BN_num_bits(priv) <= 128, "BN_priv_rand fits in 128 bits");
    BN_free(priv);

    BN_free(base); BN_free(exp); BN_free(mod); BN_free(r);
    (void)ctx;
}

/* ── main ──────────────────────────────────────────────────────────────── */
int main(void)
{
    puts("========================================");
    puts(" chibicc / OpenSSL BIGNUM test suite");
    puts("========================================");

    BN_CTX *ctx = BN_CTX_new();
    if (!ctx) { fputs("BN_CTX_new failed\n", stderr); return 1; }

    test_memory();
    test_conversion();
    test_arithmetic(ctx);
    test_modular(ctx);
    test_bitwise();
    test_comparison();
    test_gcd_prime(ctx);
    test_random(ctx);
    test_edge_cases(ctx);
    test_secure(ctx);

    BN_CTX_free(ctx);

    puts("\n========================================");
    printf(" Results: %d/%d passed", tests_passed, tests_run);
    if (tests_failed) printf("  (%d FAILED)", tests_failed);
    puts("\n========================================");

    return tests_failed ? 1 : 0;
}
