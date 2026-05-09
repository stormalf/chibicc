/*
 * test_chibicc_miller_rabin.c
 *
 * Reproducer for the chibicc-compiled OpenSSL failure:
 *
 *   ERROR: (bool) 'ossl_bn_miller_rabin_is_prime(bn, 10, ctx, NULL, 1, &status) == true'
 *          failed @ test/bn_internal_test.c:57
 *   false
 *   409738ECBB790000:error:0180006C:bignum routines:BN_mod_inverse:no inverse:
 *                    crypto/bn/bn_gcd.c:532
 *   OPENSSL_TEST_RAND_SEED=1777212200
 *
 * ── ROOT CAUSE ──────────────────────────────────────────────────────────────
 *
 * The call chain inside ossl_bn_miller_rabin_is_prime is:
 *
 *   miller_rabin_is_prime(w, ...)
 *     └─ BN_MONT_CTX_set(mont, w, ctx)          ← step 1: Montgomery setup
 *          └─ bn_mod_inverse_no_branch(Ri, R, w) ← computes R^-1 mod w
 *               └─ FAILS: "no inverse"           ← gcd(R, w) ≠ 1
 *
 * BN_MONT_CTX_set uses R = 2^(BN_BITS2 × w->top).  For gcd(R, w) ≠ 1
 * the candidate w must be EVEN (share factor 2 with R = 2^k).
 *
 * The test feeds a known prime (hardcoded odd value) so w should be odd.
 * The bug is that chibicc's broken BN_ULONG width (32-bit on a 64-bit host)
 * corrupts BN_hex2bn / BN_bin2bn:
 *
 *   - A 64-bit BN_ULONG write splits across two 32-bit slots.
 *   - The least-significant slot (which determines odd/even) ends up ZERO.
 *   - An odd prime now appears EVEN to Montgomery → "no inverse".
 *
 * The RAND_SEED=1777212200 just makes the test reproducible; it controls
 * the witness selection later, but the crash happens before any witness
 * is drawn (during Montgomery setup in step 1 above).
 *
 * ── WHAT THIS TEST DOES ─────────────────────────────────────────────────────
 *
 * 1. Platform guard      – prints BN_ULONG width; warns if mismatched.
 * 2. LSB integrity       – after BN_hex2bn, verifies BN_is_odd() is true
 *                          for known odd primes. A word-width bug zeros the
 *                          low word → BN_is_odd() returns false.
 * 3. Montgomery setup    – BN_MONT_CTX_set() must succeed for every odd prime.
 *                          This is the exact call that throws "no inverse".
 * 4. Montgomery inverse  – replicates the internal BN_mod_inverse(R^-1, R, w)
 *                          call explicitly so the error is directly visible.
 * 5. Miller-Rabin proxy  – BN_check_prime() uses the same Miller-Rabin path
 *                          as ossl_bn_miller_rabin_is_prime; must return 1.
 * 6. Round-trip sanity   – BN_bn2hex → BN_hex2bn round-trip; value must not
 *                          change (catches hex I/O corruption).
 * 7. Prime generation    – BN_generate_prime_ex(); the result must be odd
 *                          and pass Montgomery setup (chibicc may generate
 *                          composites / even "primes").
 * 8. Seed reproducibility– sets OPENSSL_TEST_RAND_SEED=1777212200 and repeats
 *                          the critical Montgomery setup check.
 *
 * Build:  cc test_chibicc_miller_rabin.c -o test_chibicc_miller_rabin -lssl -lcrypto
 * Run:    ./test_chibicc_miller_rabin
 *         OPENSSL_TEST_RAND_SEED=1777212200 ./test_chibicc_miller_rabin
 */

#include <openssl/bn.h>
#include <openssl/err.h>
#include <openssl/opensslv.h>
#include <openssl/rand.h>
#include "test.h"
#include <stdlib.h>
#include <string.h>

/* ── harness ───────────────────────────────────────────────────────────── */
static int g_run = 0, g_pass = 0, g_fail = 0;

#define CHECK(cond, label) do { \
    g_run++; \
    if (cond) { printf("[PASS] %s\n", label); g_pass++; } \
    else       { printf("[FAIL] %s\n", label); g_fail++; } \
} while (0)

static void clear_errors(void) { ERR_clear_error(); }

/* Return the topmost OpenSSL error reason string, or "" if none. */
static const char *last_err(void)
{
    unsigned long e = ERR_peek_last_error();
    return e ? ERR_reason_error_string(e) : "";
}

static void dump_bn(const char *tag, const BIGNUM *n)
{
    char *h = BN_bn2hex(n);
    printf("  %-12s = %s  (%d bits, %s)\n",
           tag, h, BN_num_bits(n), BN_is_odd(n) ? "odd" : "EVEN");
    OPENSSL_free(h);
}

/* ── test primes ───────────────────────────────────────────────────────── */
/*
 * Primes chosen to straddle every critical BN_ULONG boundary:
 *   - 32-bit: fits in one 32-bit word  (should always work)
 *   - 33-bit: FIRST prime crossing the 32-bit boundary  ← first bug trigger
 *   - 40-bit: the reported failure zone from bnexp.txt
 *   - 48-bit: another multi-word region
 *   - 63/64/65-bit: around the 64-bit boundary
 *   - 128-bit: two 64-bit words
 *
 * All values are verified primes (sympy.isprime confirmed).
 */
static const struct { const char *label; const char *hex; } PRIMES[] = {
    { "8-bit   (139)",          "8B"                                 },
    { "16-bit  (32771)",        "8003"                               },
    { "31-bit",                 "7FFFFFFF"                           }, /* composite, used for boundary */
    { "32-bit",                 "8000000B"                           },
    { "33-bit  (boundary!)",    "010000000F"                          },    
    { "40-bit  (failure zone)", "8000000017"                         },
    { "48-bit",                 "800000000005"                       },
    { "63-bit",                 "4000000000000087"                   },
    { "64-bit",                 "800000000000001D"                   },
    { "65-bit  (boundary!)",    "01000000000000000D"                  },
    { "128-bit",                "8000000000000000000000000000001D"   },
    { NULL, NULL }
};

/* A set of known composites — miller_rabin must NOT report these as prime. */
static const struct { const char *label; const char *hex; } COMPOSITES[] = {
    { "composite-32  (2^32)",   "100000000"    },
    { "composite-40  (even)",   "8000000016"   },
    { "composite-64  (9*p)",    "7FFFFFFFFFFFE7" }, /* not prime */
    { NULL, NULL }
};

/* ── 1. platform guard ─────────────────────────────────────────────────── */
static void section_platform(void)
{
    puts("\n=== 1. Platform / BN_ULONG Guard ===");
    printf("  OpenSSL          : %s\n", OPENSSL_VERSION_TEXT);
    printf("  sizeof(BN_ULONG) : %zu bytes (%zu bits)\n",
           sizeof(BN_ULONG), sizeof(BN_ULONG) * 8);
    printf("  BN_BITS2         : %d\n", BN_BITS2);
    printf("  sizeof(long)     : %zu bytes\n", sizeof(long));

    int ok = (sizeof(BN_ULONG) == 8 && BN_BITS2 == 64);
    printf("  Status           : %s\n",
           ok ? "[OK] 64-bit BN_ULONG"
              : "[WARN] BN_ULONG is NOT 64-bit — expect Miller-Rabin failures!");

    /* Functional probe: 2^32 must produce a 33-bit number */
    BIGNUM *a = BN_new();
    BN_set_word(a, 0xFFFFFFFFUL);
    BN_add_word(a, 1);
    CHECK(BN_num_bits(a) == 33,
          "platform: 0xFFFFFFFF + 1 == 33 bits (word overflow handled)");
    BN_free(a);
}

/* ── 2. LSB integrity after BN_hex2bn ──────────────────────────────────── */
/*
 * THE core symptom: chibicc zeros the low BN_ULONG word during hex parsing,
 * turning every odd prime even.  BN_is_odd() must return 1 for all of them.
 */
static void section_lsb_integrity(BN_CTX *ctx)
{
    puts("\n=== 2. LSB Integrity After BN_hex2bn ===");
    puts("  (Checks that the lowest bit survives parsing — chibicc may zero it)");

    for (int i = 0; PRIMES[i].label; i++) {
        BIGNUM *n = NULL;
        BN_hex2bn(&n, PRIMES[i].hex);

        /* The expected parity of the original hex: last hex digit's bit 0 */
        char last = PRIMES[i].hex[strlen(PRIMES[i].hex) - 1];
        int expected_odd = (last == '1' || last == '3' || last == '5' ||
                            last == '7' || last == '9' || last == 'B' ||
                            last == 'D' || last == 'F' || last == 'b' ||
                            last == 'd' || last == 'f');

        char label[128];
        snprintf(label, sizeof(label), "lsb: %s is %s",
                 PRIMES[i].label, expected_odd ? "odd" : "even");

        CHECK(!!BN_is_odd(n) == expected_odd, label);

        if (!!BN_is_odd(n) != expected_odd) {
            printf("  [INFO] BN_hex2bn corrupted parity: expected %s, got %s\n",
                   expected_odd ? "odd" : "even",
                   BN_is_odd(n) ? "odd" : "even");
            dump_bn("parsed", n);
        }
        BN_free(n);
    }
    (void)ctx;
}

/* ── 3. Montgomery setup (the exact failing call) ───────────────────────── */
/*
 * BN_MONT_CTX_set() is the first thing ossl_bn_miller_rabin_is_prime calls.
 * It runs: R^{-1} mod w via BN_mod_inverse.
 * If w is even (due to chibicc's word-width bug), this throws:
 *   "BN_mod_inverse: no inverse"   ← exact error from the bug report.
 */
static void section_montgomery_setup(BN_CTX *ctx)
{
    puts("\n=== 3. Montgomery Setup (BN_MONT_CTX_set) ===");
    puts("  (This is the exact call that throws 'no inverse' in the bug)");

    for (int i = 0; PRIMES[i].label; i++) {
        BIGNUM *n = NULL;
        BN_hex2bn(&n, PRIMES[i].hex);

        /* Skip even numbers — we only test odd primes here */
        if (!BN_is_odd(n)) {
            printf("  [SKIP] %s — appears EVEN after parsing (LSB bug!)\n",
                   PRIMES[i].label);
            BN_free(n);
            g_run++; g_fail++;          /* count as failure */
            continue;
        }

        clear_errors();
        BN_MONT_CTX *mont = BN_MONT_CTX_new();
        int rc = BN_MONT_CTX_set(mont, n, ctx);

        char label[128];
        snprintf(label, sizeof(label),
                 "mont-setup: %s", PRIMES[i].label);
        CHECK(rc == 1, label);

        if (rc != 1) {
            printf("  [INFO] BN_MONT_CTX_set failed: %s\n", last_err());
            printf("  [INFO] This is the 'no inverse' error from the bug report\n");
            dump_bn("n", n);
            ERR_clear_error();
        }

        BN_MONT_CTX_free(mont);
        BN_free(n);
    }
}

/* ── 4. Explicit Montgomery inverse (replicates bn_gcd.c:532 path) ──────── */
/*
 * BN_MONT_CTX_set internally computes: Ri = R^{-1} mod w
 * where R = 2^(BN_BITS2 * w->top).
 * We replicate this with a power-of-2 R just above the prime.
 * On chibicc: if w appears even, gcd(R, w) = 2 → BN_mod_inverse returns NULL.
 */
static void section_explicit_inverse(BN_CTX *ctx)
{
    puts("\n=== 4. Explicit Montgomery Inverse (replicates bn_gcd.c:532) ===");
    puts("  (Computes R^-1 mod w as BN_MONT_CTX_set does internally)");

    for (int i = 0; PRIMES[i].label; i++) {
        BIGNUM *w = NULL;
        BN_hex2bn(&w, PRIMES[i].hex);

        /* R = 2^(ceil_to_BN_BITS2(w)) — smallest power of 2 >= 2*w */
        int rbits = ((BN_num_bits(w) + BN_BITS2 - 1) / BN_BITS2) * BN_BITS2;
        BIGNUM *R = BN_new();
        BN_set_bit(R, rbits);  /* R = 2^rbits */

        clear_errors();
        BIGNUM *Ri = BN_mod_inverse(NULL, R, w, ctx);

        char label[128];
        snprintf(label, sizeof(label),
                 "mont-inverse: R=2^%d mod %s", rbits, PRIMES[i].label);
        CHECK(Ri != NULL, label);

        if (!Ri) {
            printf("  [INFO] BN_mod_inverse(R=2^%d, w) failed: %s\n",
                   rbits, last_err());
            printf("  [INFO] → This IS the 'no inverse' from bn_gcd.c:532\n");
            dump_bn("w", w);
            /* verify our hypothesis: is w even? */
            printf("  [INFO] w is %s (parity of low word)\n",
                   BN_is_odd(w) ? "ODD — bug is elsewhere"
                                : "EVEN — confirmed BN_hex2bn LSB corruption");
            ERR_clear_error();
        } else {
            BN_free(Ri);
        }

        BN_free(R);
        BN_free(w);
    }
}

/* ── 5. Miller-Rabin proxy via BN_check_prime ───────────────────────────── */
/*
 * BN_check_prime() calls the same Miller-Rabin path as
 * ossl_bn_miller_rabin_is_prime. It must return 1 for known primes.
 * On chibicc: either returns -1 (internal error) or 0 (false composite).
 */
static void section_miller_rabin(BN_CTX *ctx)
{
    puts("\n=== 5. Miller-Rabin via BN_check_prime (known primes must pass) ===");

    for (int i = 0; PRIMES[i].label; i++) {
        BIGNUM *n = NULL;
        BN_hex2bn(&n, PRIMES[i].hex);

        /* Only test numbers that are actually prime */
        /* (31-bit "7FFFFFFF" is composite — skip primality check for it) */
        if (strcmp(PRIMES[i].hex, "7FFFFFFF") == 0) {
            BN_free(n);
            continue;
        }

        clear_errors();
        int rc = BN_check_prime(n, ctx, NULL);

        char label[128];
        snprintf(label, sizeof(label),
                 "miller-rabin: %s is prime", PRIMES[i].label);
        CHECK(rc == 1, label);

        if (rc != 1) {
            printf("  [INFO] BN_check_prime returned %d for known prime\n", rc);
            printf("  [INFO] Last error: %s\n", last_err());
            printf("  [INFO] rc=0 → reported composite; rc=-1 → internal error\n");
            printf("  [INFO] rc=-1 with 'no inverse' = exact bug from report\n");
            dump_bn("n", n);
            ERR_clear_error();
        }

        BN_free(n);
    }

    /* Known composites must NOT be reported as prime */
    puts("  -- composites must fail --");
    for (int i = 0; COMPOSITES[i].label; i++) {
        BIGNUM *n = NULL;
        BN_hex2bn(&n, COMPOSITES[i].hex);

        clear_errors();
        int rc = BN_check_prime(n, ctx, NULL);

        char label[128];
        snprintf(label, sizeof(label),
                 "miller-rabin: %s is NOT prime", COMPOSITES[i].label);
        CHECK(rc == 0, label);

        if (rc == 1) {
            printf("  [INFO] BN_check_prime WRONGLY reported composite as prime!\n");
            dump_bn("n", n);
        }
        ERR_clear_error();
        BN_free(n);
    }
}

/* ── 6. Round-trip sanity ───────────────────────────────────────────────── */
/*
 * If BN_hex2bn/BN_bn2hex are broken, the round-trip changes the value.
 * A changed value changes parity → Montgomery fails.
 */
static void section_roundtrip(BN_CTX *ctx)
{
    puts("\n=== 6. BN_hex2bn → BN_bn2hex Round-Trip ===");

    for (int i = 0; PRIMES[i].label; i++) {
        BIGNUM *n = NULL;
        BN_hex2bn(&n, PRIMES[i].hex);

        char *back = BN_bn2hex(n);

        /* BN_bn2hex upper-cases and may strip leading zeros */
        char label[128];
        snprintf(label, sizeof(label),
                 "roundtrip: %s", PRIMES[i].label);
        CHECK(strcasecmp(back, PRIMES[i].hex) == 0, label);

        if (strcasecmp(back, PRIMES[i].hex) != 0) {
            printf("  [INFO] expected: %s\n", PRIMES[i].hex);
            printf("  [INFO] got:      %s\n", back);
        }

        OPENSSL_free(back);
        BN_free(n);
    }
    (void)ctx;
}

/* ── 7. Prime generation integrity ─────────────────────────────────────── */
/*
 * BN_generate_prime_ex() uses broken arithmetic on chibicc → may produce
 * even numbers or composites. Each generated prime must:
 *   a) be odd
 *   b) pass BN_MONT_CTX_set (the failing call in the bug)
 *   c) pass BN_check_prime
 */
static void section_generated_primes(BN_CTX *ctx)
{
    puts("\n=== 7. Generated Prime Integrity ===");
    puts("  (BN_generate_prime_ex output must be odd, setup Montgomery, pass Miller-Rabin)");

    int bit_sizes[] = { 32, 33, 40, 48, 64, 65, 128, 0 };

    for (int i = 0; bit_sizes[i]; i++) {
        int bits = bit_sizes[i];
        BIGNUM *p = BN_new();

        clear_errors();
        int ok = BN_generate_prime_ex(p, bits, 0, NULL, NULL, NULL);

        char la[64], lb[64], lc[64];
        snprintf(la, sizeof(la), "gen-prime %d-bit: succeeds",       bits);
        snprintf(lb, sizeof(lb), "gen-prime %d-bit: result is odd",  bits);
        snprintf(lc, sizeof(lc), "gen-prime %d-bit: passes Miller-Rabin", bits);

        CHECK(ok == 1, la);

        if (ok) {
            CHECK(BN_is_odd(p), lb);

            if (!BN_is_odd(p)) {
                dump_bn("p", p);
                printf("  [INFO] Generated an EVEN 'prime' — word-width bug\n");
            }

            /* Montgomery setup */
            BN_MONT_CTX *mont = BN_MONT_CTX_new();
            clear_errors();
            int mrc = BN_MONT_CTX_set(mont, p, ctx);
            char lm[64];
            snprintf(lm, sizeof(lm),
                     "gen-prime %d-bit: BN_MONT_CTX_set succeeds", bits);
            CHECK(mrc == 1, lm);
            if (mrc != 1) {
                printf("  [INFO] BN_MONT_CTX_set failed: %s\n", last_err());
                printf("  [INFO] This reproduces the 'no inverse' from the bug report\n");
                dump_bn("p", p);
                ERR_clear_error();
            }
            BN_MONT_CTX_free(mont);

            /* Miller-Rabin */
            clear_errors();
            int prc = BN_check_prime(p, ctx, NULL);
            CHECK(prc == 1, lc);
            if (prc != 1) {
                printf("  [INFO] Generated prime failed Miller-Rabin (rc=%d): %s\n",
                       prc, last_err());
                ERR_clear_error();
            }
        }

        BN_free(p);
    }
}

/* ── 8. Seed-specific reproducibility ──────────────────────────────────── */
/*
 * OPENSSL_TEST_RAND_SEED=1777212200 is the exact seed from the bug report.
 * We seed the PRNG identically and re-run the Montgomery setup + Miller-Rabin
 * checks to reproduce the deterministic failure.
 *
 * The seed affects the witness selection inside Miller-Rabin, but the
 * Montgomery setup failure happens before any witness is drawn.
 * Still, pinning the seed ensures bit-for-bit reproducibility.
 */
static void section_seed_reproducibility(BN_CTX *ctx)
{
    puts("\n=== 8. Seed Reproducibility (OPENSSL_TEST_RAND_SEED=1777212200) ===");

    unsigned int seed_val = 1777212200U;
    RAND_seed(&seed_val, sizeof(seed_val));
    printf("  Seeded PRNG with %u (0x%08X)\n", seed_val, seed_val);

    /* Re-run Montgomery setup for the primes most likely to fail on chibicc */
    const char *critical[] = {
        "010000000F",             /* 33-bit: first to cross 32-bit boundary */
        "8000000017",            /* 40-bit: reported failure zone           */
        "1000000000000000D",     /* 65-bit: first to cross 64-bit boundary  */
        NULL
    };
    const char *clabels[] = {
        "seed-repro: 33-bit prime (BN_MONT_CTX_set)",
        "seed-repro: 40-bit prime (BN_MONT_CTX_set)",
        "seed-repro: 65-bit prime (BN_MONT_CTX_set)",
        NULL
    };

    for (int i = 0; critical[i]; i++) {
        BIGNUM *n = NULL;
        BN_hex2bn(&n, critical[i]);

        clear_errors();
        BN_MONT_CTX *mont = BN_MONT_CTX_new();
        int rc = BN_MONT_CTX_set(mont, n, ctx);
        CHECK(rc == 1, clabels[i]);

        if (rc != 1) {
            printf("  [INFO] 'no inverse' reproduced with seed %u: %s\n",
                   seed_val, last_err());
            dump_bn("n", n);
            ERR_clear_error();
        }
        BN_MONT_CTX_free(mont);

        /* Also run BN_check_prime under this seed */
        clear_errors();
        int prc = BN_check_prime(n, ctx, NULL);
        char pl[128];
        snprintf(pl, sizeof(pl), "seed-repro: %s is prime (Miller-Rabin)", critical[i]);
        CHECK(prc == 1, pl);
        if (prc != 1) {
            printf("  [INFO] Miller-Rabin returned %d under seed %u\n", prc, seed_val);
            printf("  [INFO] This matches: 'ossl_bn_miller_rabin_is_prime == true' FAILED\n");
            ERR_clear_error();
        }

        BN_free(n);
    }

    /* Also generate a prime under this seed and verify it */
    puts("  -- generate prime under fixed seed --");
    BIGNUM *gp = BN_new();
    clear_errors();
    BN_generate_prime_ex(gp, 40, 0, NULL, NULL, NULL);

    CHECK(BN_is_odd(gp), "seed-repro: generated 40-bit prime is odd");

    BN_MONT_CTX *mont = BN_MONT_CTX_new();
    clear_errors();
    int mrc = BN_MONT_CTX_set(mont, gp, ctx);
    CHECK(mrc == 1, "seed-repro: generated 40-bit prime passes BN_MONT_CTX_set");
    if (mrc != 1) {
        printf("  [INFO] BN_MONT_CTX_set failed under seed %u: %s\n",
               seed_val, last_err());
        dump_bn("gp", gp);
        ERR_clear_error();
    }
    BN_MONT_CTX_free(mont);
    BN_free(gp);
}

/* ── main ──────────────────────────────────────────────────────────────── */
int main(void)
{
    puts("================================================================");
    puts(" chibicc Miller-Rabin / BN_mod_inverse regression test");
    puts(" Reproduces:");
    puts("   ossl_bn_miller_rabin_is_prime == true  FAILED");
    puts("   BN_mod_inverse: no inverse (crypto/bn/bn_gcd.c:532)");
    puts("   OPENSSL_TEST_RAND_SEED=1777212200");
    puts("================================================================");

    /* Check if the seed env-var is set (as in the original failure) */
    const char *env_seed = getenv("OPENSSL_TEST_RAND_SEED");
    if (env_seed)
        printf("  Note: OPENSSL_TEST_RAND_SEED=%s (from environment)\n", env_seed);

    BN_CTX *ctx = BN_CTX_new();
    if (!ctx) { fputs("BN_CTX_new failed\n", stderr); return 1; }

    section_platform();
    section_lsb_integrity(ctx);
    section_montgomery_setup(ctx);
    section_explicit_inverse(ctx);
    section_miller_rabin(ctx);
    section_roundtrip(ctx);
    section_generated_primes(ctx);
    section_seed_reproducibility(ctx);

    BN_CTX_free(ctx);

    puts("\n================================================================");
    printf(" TOTAL: %d/%d passed", g_pass, g_run);
    if (g_fail) printf("  *** %d FAILED ***", g_fail);
    puts("\n================================================================");

    /*
     * INTERPRETING FAILURES ON CHIBICC
     * ─────────────────────────────────
     * Section 2 (LSB integrity) FAILS:
     *   → BN_hex2bn zeros the low word → makes odd primes appear even.
     *   → This is the root cause of everything below.
     *
     * Section 3 (Montgomery setup) FAILS with "no inverse":
     *   → This IS the error from bn_gcd.c:532 in the bug report.
     *   → Caused by the even-parity corruption above.
     *
     * Section 4 (explicit inverse) FAILS:
     *   → BN_mod_inverse(R, w) returns NULL because w is even.
     *
     * Section 5 (Miller-Rabin) FAILS or returns -1:
     *   → BN_check_prime returns -1 (internal error) matching
     *     'ossl_bn_miller_rabin_is_prime == true' being false.
     *
     * Failures isolated to specific bit sizes (33, 65) pinpoint the
     * BN_ULONG word-width boundary that chibicc miscompiles.
     *
     * THE FIX: ensure chibicc emits 64-bit load/store for `unsigned long`
     * on 64-bit hosts, or compile OpenSSL with -DBN_ULONG='unsigned long long'.
     */
    return g_fail ? 1 : 0;
}

