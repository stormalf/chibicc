/*
 * test_chibicc_openssl_sk.c  (v2 – uses publicly exported stack types)
 *
 * Regression tests reproducing the "undefined reference to sk_*" and
 * "undefined reference to ossl_check_*_sk_type" link errors that occur
 * when OpenSSL is compiled with chibicc.
 *
 * Root cause
 * ----------
 * OpenSSL generates type-safe stack wrappers via DEFINE_STACK_OF(T) in
 * <openssl/safestack.h>.  With gcc/clang these expand to static inline
 * functions emitted in every translation unit that includes the header.
 * chibicc does not handle the underlying _Generic / compound-expression
 * patterns correctly, so the wrappers are never emitted and every call
 * site becomes an "undefined reference" at link time.
 *
 * Why v1 failed
 * -------------
 * OSSL_STORE_INFO is an *internal* OpenSSL type; DEFINE_STACK_OF for it
 * is only called inside the engine sources, not in any public header.
 * gcc therefore also cannot find sk_OSSL_STORE_INFO_*.
 * This version uses X509, X509_NAME and GENERAL_NAME whose stacks are
 * declared in public headers and are present in -lcrypto.
 *
 * Build (should succeed with gcc/clang, fails to link with chibicc):
 *
 *   gcc -o test_sk test_chibicc_openssl_sk.c \
 *       $(pkg-config --cflags --libs openssl)
 *
 *   chibicc -o test_sk test_chibicc_openssl_sk.c \
 *       $(pkg-config --cflags --libs openssl)
 */

#include "test.h"
#include <stdlib.h>
#include <string.h>

#include <openssl/x509.h>      /* DEFINE_STACK_OF(X509), ossl_check_* */
#include <openssl/x509v3.h>    /* DEFINE_STACK_OF(GENERAL_NAME)        */
#include <openssl/safestack.h>
#include <openssl/err.h>

/* ------------------------------------------------------------------ */
/* Minimal harness                                                      */
/* ------------------------------------------------------------------ */
static int g_run = 0, g_pass = 0, g_fail = 0;

#define PASS(n)     do { printf("[PASS] %s\n",(n)); g_pass++; g_run++; } while(0)
#define FAIL(n,r)   do { printf("[FAIL] %s -- %s\n",(n),(r)); \
                         ERR_print_errors_fp(stderr); \
                         g_fail++; g_run++; } while(0)

/* ------------------------------------------------------------------ */
/* Test 1 – sk_X509_new_null                                            */
/* Mirrors e_loader_attic.c:348  sk_OSSL_STORE_INFO_new_null()          */
/* ------------------------------------------------------------------ */
static void test_sk_new_null(void)
{
    const char *n = "sk_X509_new_null";
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "returned NULL"); return; }
    sk_X509_free(sk);
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 2 – sk_X509_push  (three call sites)                            */
/* Mirrors e_loader_attic.c:353, :362, :372                             */
/* ------------------------------------------------------------------ */
static void test_sk_push(void)
{
    const char *n = "sk_X509_push (x3 sites)";
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    for (int i = 0; i < 3; i++) {
        X509 *c = X509_new();
        if (!c || sk_X509_push(sk, c) <= 0) {
            X509_free(c);
            sk_X509_pop_free(sk, X509_free);
            FAIL(n, "push"); return;
        }
    }
    sk_X509_pop_free(sk, X509_free);
    PASS(n);
}

#define ATTR_UNUSED __attribute__((unused))

static ATTR_UNUSED inline int mul(int a, int b)
{
    return a * b;
}

int test(void)
{
    return mul(2, 3);
}


typedef struct stack_st_FOO stack_st_FOO;

typedef void (*freefunc)(void *a);

static inline void free_thunk(freefunc f, void *p)
{
    f(p);
}

static inline void stack_free(stack_st_FOO *s, freefunc f)
{
    free_thunk(f, s);
}

void caller(stack_st_FOO *s, freefunc f)
{
    stack_free(s, f);
}

/* ------------------------------------------------------------------ */
/* Test 3 – sk_X509_num                                                 */
/* Mirrors e_loader_attic.c:406  (eof_PKCS12)                           */
/* ------------------------------------------------------------------ */
static void test_sk_num(void)
{
    const char *n = "sk_X509_num";
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    if (sk_X509_num(sk) != 0) {
        sk_X509_free(sk); FAIL(n, "empty stack num != 0"); return;
    }
    X509 *c = X509_new();
    if (!c) { sk_X509_free(sk); FAIL(n, "X509_new"); return; }
    sk_X509_push(sk, c);
    if (sk_X509_num(sk) != 1) {
        sk_X509_pop_free(sk, X509_free); FAIL(n, "num != 1 after push"); return;
    }
    sk_X509_pop_free(sk, X509_free);
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 4 – sk_X509_shift                                               */
/* Mirrors e_loader_attic.c:398                                         */
/* ------------------------------------------------------------------ */
static void test_sk_shift(void)
{
    const char *n = "sk_X509_shift";
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    X509 *c = X509_new();
    if (!c) { sk_X509_free(sk); FAIL(n, "X509_new"); return; }
    sk_X509_push(sk, c);

    X509 *shifted = sk_X509_shift(sk);
    if (!shifted) {
        sk_X509_pop_free(sk, X509_free);
        FAIL(n, "shift returned NULL on non-empty stack"); return;
    }
    X509_free(shifted);

    if (sk_X509_num(sk) != 0) {
        sk_X509_free(sk); FAIL(n, "stack non-empty after last shift"); return;
    }
    sk_X509_free(sk);
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 5 – sk_X509_pop_free                                            */
/* Mirrors e_loader_attic.c:385 (error path) and :413 (destroy_ctx)    */
/* ------------------------------------------------------------------ */
static void test_sk_pop_free(void)
{
    const char *n = "sk_X509_pop_free";
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    for (int i = 0; i < 4; i++) {
        X509 *c = X509_new();
        if (!c) { sk_X509_pop_free(sk, X509_free); FAIL(n, "X509_new"); return; }
        sk_X509_push(sk, c);
    }
    sk_X509_pop_free(sk, X509_free);   /* must not crash / leak */
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 6 – ossl_check_const_X509_sk_type                               */
/* Mirrors openssl/x509.h:79-80  (try_decode_PKCS12)                    */
/* ------------------------------------------------------------------ */
static void test_ossl_check_const_sk_type(void)
{
    const char *n = "ossl_check_const_X509_sk_type";
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    const STACK_OF(X509) *csk = sk;
    /* static inline identity; symbol absent with chibicc → undef ref */
    const OPENSSL_STACK *raw = ossl_check_const_X509_sk_type(csk);
    (void)raw;

    sk_X509_free(sk);
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 7 – ossl_check_X509_sk_type                                     */
/* Mirrors openssl/x509.h:92  (try_decode_PKCS12)                       */
/* ------------------------------------------------------------------ */
static void test_ossl_check_sk_type(void)
{
    const char *n = "ossl_check_X509_sk_type";
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    OPENSSL_STACK *raw = ossl_check_X509_sk_type(sk);
    (void)raw;

    sk_X509_free(sk);
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 8 – sk_X509_NAME lifecycle (second DEFINE_STACK_OF type)        */
/* ------------------------------------------------------------------ */
static void test_sk_X509_NAME_lifecycle(void)
{
    const char *n = "sk_X509_NAME_lifecycle";
    STACK_OF(X509_NAME) *sk = sk_X509_NAME_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    X509_NAME *nm = X509_NAME_new();
    if (!nm) { sk_X509_NAME_free(sk); FAIL(n, "X509_NAME_new"); return; }

    if (sk_X509_NAME_push(sk, nm) <= 0) {
        X509_NAME_free(nm); sk_X509_NAME_free(sk); FAIL(n, "push"); return;
    }
    if (sk_X509_NAME_num(sk) != 1) {
        sk_X509_NAME_pop_free(sk, X509_NAME_free);
        FAIL(n, "num != 1"); return;
    }
    sk_X509_NAME_pop_free(sk, X509_NAME_free);
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 9 – sk_GENERAL_NAME lifecycle (third DEFINE_STACK_OF type)      */
/* ------------------------------------------------------------------ */
static void test_sk_GENERAL_NAME_lifecycle(void)
{
    const char *n = "sk_GENERAL_NAME_lifecycle";
    STACK_OF(GENERAL_NAME) *sk = sk_GENERAL_NAME_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    GENERAL_NAME *gn = GENERAL_NAME_new();
    if (!gn) { sk_GENERAL_NAME_free(sk); FAIL(n, "GENERAL_NAME_new"); return; }

    if (sk_GENERAL_NAME_push(sk, gn) <= 0) {
        GENERAL_NAME_free(gn); sk_GENERAL_NAME_free(sk); FAIL(n, "push"); return;
    }

    GENERAL_NAME *shifted = sk_GENERAL_NAME_shift(sk);
    if (!shifted) {
        sk_GENERAL_NAME_pop_free(sk, GENERAL_NAME_free);
        FAIL(n, "shift returned NULL"); return;
    }
    GENERAL_NAME_free(shifted);
    sk_GENERAL_NAME_free(sk);
    PASS(n);
}

/* ------------------------------------------------------------------ */
/* Test 10 – full round-trip mirroring try_decode_PKCS12 flow           */
/* ------------------------------------------------------------------ */
static void test_full_stack_round_trip(void)
{
    const char *n = "full_stack_round_trip";

    /* allocate  (line 348) */
    STACK_OF(X509) *sk = sk_X509_new_null();
    if (!sk) { FAIL(n, "new_null"); return; }

    /* push 3 (lines 353, 362, 372) */
    for (int i = 0; i < 3; i++) {
        X509 *c = X509_new();
        if (!c || sk_X509_push(sk, c) <= 0) {
            X509_free(c); sk_X509_pop_free(sk, X509_free);
            FAIL(n, "push in loop"); return;
        }
    }

    /* eof_PKCS12: num check (line 406) */
    if (sk_X509_num(sk) != 3) {
        sk_X509_pop_free(sk, X509_free); FAIL(n, "num != 3"); return;
    }

    /* consume via shift (line 398) */
    X509 *item = sk_X509_shift(sk);
    if (!item) {
        sk_X509_pop_free(sk, X509_free); FAIL(n, "shift"); return;
    }
    X509_free(item);

    if (sk_X509_num(sk) != 2) {
        sk_X509_pop_free(sk, X509_free); FAIL(n, "num != 2 after shift"); return;
    }

    /* destroy_ctx / error path pop_free (lines 385, 413) */
    sk_X509_pop_free(sk, X509_free);

    /* ossl_check_* type guards (x509.h:79,80,92) */
    STACK_OF(X509) *sk2 = sk_X509_new_null();
    if (!sk2) { FAIL(n, "new_null #2"); return; }
    const STACK_OF(X509) *csk2 = sk2;
    (void)ossl_check_const_X509_sk_type(csk2);
    (void)ossl_check_X509_sk_type(sk2);
    sk_X509_free(sk2);

    PASS(n);
}

/* ------------------------------------------------------------------ */
int main(void)
{
    printf("=== chibicc / OpenSSL sk_* undefined-reference regression tests ===\n\n");

    test_sk_new_null();
    test_sk_push();
    test_sk_num();
    test_sk_shift();
    test_sk_pop_free();
    test_ossl_check_const_sk_type();
    test_ossl_check_sk_type();
    test_sk_X509_NAME_lifecycle();
    test_sk_GENERAL_NAME_lifecycle();
    test_full_stack_round_trip();

    printf("\n--- %d/%d passed", g_pass, g_run);
    if (g_fail) printf(", %d FAILED", g_fail);
    printf(" ---\n");
    return g_fail ? EXIT_FAILURE : EXIT_SUCCESS;
}
