
/* test_choose_expr.c
 *
 * Stress-tests __builtin_choose_expr for chibicc edge cases.
 *
 * GCC semantics (the spec chibicc must match):
 *   __builtin_choose_expr(COND, EXPR_TRUE, EXPR_FALSE)
 *   - COND must be an integer constant expression.
 *   - Only the SELECTED branch is evaluated / type-checked / linked.
 *   - The NOT-selected branch may be ill-typed or call an undefined
 *     function without causing a compile or link error.
 *   - The result is an lvalue when the selected branch is an lvalue.
 *
 * Compile (GCC — all should pass):
 *   gcc -std=gnu11 -Wall -Wextra test_choose_expr.c -o test_choose_expr
 *   ./test_choose_expr && echo "ALL PASSED"
 *
 * Compile (chibicc — exposes bugs):
 *   chibicc test_choose_expr.c -o test_choose_expr
 *
 * Each test is labelled with the chibicc failure mode it targets.
 */

#include <stdio.h>
#include <assert.h>
#include <stdint.h>

static int g_pass = 0;
static int g_fail = 0;

#define PASS(name) do { printf("PASS  %s\n", name); g_pass++; } while(0)
#define FAIL(name) do { printf("FAIL  %s\n", name); g_fail++; } while(0)
#define CHECK(name, cond) do { if(cond) PASS(name); else FAIL(name); } while(0)

/* ================================================================== *
 * EDGE CASE 1: Unevaluated branch calls an undefined function.       *
 *                                                                     *
 * Buggy chibicc: emits a relocation for `undefined_fn` even when     *
 * the false branch is not selected → linker error.                   *
 * ================================================================== */
int undefined_fn(void);   /* declared, never defined — intentional */

static void test_unevaluated_branch_linkage(void) {
    int r = __builtin_choose_expr(1,
                42,
                undefined_fn()   /* must NOT be linked */
             );
    CHECK("EC1: unevaluated branch — no linker ref", r == 42);
}

/* ================================================================== *
 * EDGE CASE 2: Unevaluated branch is ill-typed.                      *
 *                                                                     *
 * GCC accepts this: the non-selected branch is never type-checked.   *
 * Buggy chibicc: may reject at parse/type-check time.                *
 * ================================================================== */
static void test_ill_typed_branch(void) {
    int *p = (int[]){7};
    /* false branch dereferences a void* without cast — ill-typed,
       but must be silently ignored because COND == 1.             */
    int r = __builtin_choose_expr(1,
                *p,
                *(void *)0   /* ill-typed; must not be evaluated */
             );
    CHECK("EC2: ill-typed false branch ignored", r == 7);
}

/* ================================================================== *
 * EDGE CASE 3: Result is an lvalue (the selected branch is a var).   *
 *                                                                     *
 * GCC: __builtin_choose_expr yields an lvalue when selected branch   *
 * is an lvalue; you can take its address or assign through it.       *
 * Buggy chibicc: may yield an rvalue copy, breaking &-of-result.    *
 * ================================================================== */
static void test_lvalue_result(void) {
    int a = 10, b = 20;
    __builtin_choose_expr(1, a, b) = 99;   /* assign through lvalue */
    CHECK("EC3: lvalue result — assign through selected branch", a == 99 && b == 20);

    int *ptr = &__builtin_choose_expr(0, a, b);
    CHECK("EC3: lvalue result — address of false branch", ptr == &b);
}

/* ================================================================== *
 * EDGE CASE 4: Nested __builtin_choose_expr.                         *
 *                                                                     *
 * Buggy chibicc: may mis-parse deeply nested ternary-like trees,     *
 * or eagerly evaluate all inner nodes.                               *
 * ================================================================== */
static void test_nested(void) {
    int r =
        __builtin_choose_expr(1,
            __builtin_choose_expr(0,
                undefined_fn(),         /* must NOT be linked (inner false, outer true→inner) */
                100
            ),
            undefined_fn()             /* must NOT be linked (outer false) */
        );
    CHECK("EC4: nested — only innermost selected branch linked", r == 100);
}

/* ================================================================== *
 * EDGE CASE 5: Condition is a sizeof / offsetof expression.          *
 *                                                                     *
 * COND must be an integer constant expression; sizeof qualifies.     *
 * Buggy chibicc: may fail to constant-fold sizeof in the condition.  *
 * ================================================================== */
static void test_sizeof_condition(void) {
    int r = __builtin_choose_expr(
                sizeof(int) == 4,
                1,
                undefined_fn()
             );
    CHECK("EC5: sizeof condition constant-folded", r == 1);

    int s = __builtin_choose_expr(
                sizeof(long) >= 4,
                (int)sizeof(long),
                -1
             );
    CHECK("EC5: sizeof in both condition and branch", s >= 4);
}

/* ================================================================== *
 * EDGE CASE 6: Condition is a __builtin_constant_p expression.       *
 *                                                                     *
 * Common OpenSSL/crypto pattern: dispatch on whether a value is a    *
 * compile-time constant (e.g. to pick a constant-time path).        *
 * Buggy chibicc: __builtin_constant_p may not return a constant      *
 * expression suitable as a __builtin_choose_expr condition.          *
 * ================================================================== */
static void test_constant_p_condition(void) {
    int r = __builtin_choose_expr(
                __builtin_constant_p(42),
                1,      /* 42 IS a constant — expect this */
                0
             );
    CHECK("EC6: __builtin_constant_p(literal) == 1", r == 1);

    volatile int v = 5;
    int s = __builtin_choose_expr(
                __builtin_constant_p(v),
                1,
                0       /* v is NOT a constant — expect this */
             );
    CHECK("EC6: __builtin_constant_p(volatile) == 0", s == 0);
}

/* ================================================================== *
 * EDGE CASE 7: Type of result matches selected branch, not the other.*
 *                                                                     *
 * Unlike ?: which performs usual arithmetic conversions on BOTH arms, *
 * __builtin_choose_expr preserves the type of the selected branch    *
 * exactly. Buggy chibicc: may apply conversions across both arms.    *
 * ================================================================== */
static void test_type_preservation(void) {
    /* selected branch is (char)1; result type must be char, not int */
    __typeof__(__builtin_choose_expr(1, (char)1, (long long)0)) x = 0;
    CHECK("EC7: result type is char (sizeof==1)", sizeof(x) == 1);

    /* selected branch is (long long)0; result type must be long long */
    __typeof__(__builtin_choose_expr(0, (char)1, (long long)0)) y = 0;
    CHECK("EC7: result type is long long (sizeof==8)", sizeof(y) == 8);
}

/* ================================================================== *
 * EDGE CASE 8: __builtin_choose_expr inside a macro used as          *
 * a function-like dispatch (the real OpenSSL pattern).               *
 *                                                                     *
 * Buggy chibicc: macro expansion + choose_expr interaction may       *
 * cause the non-selected function pointer to be referenced.          *
 * ================================================================== */
static int real_impl(int x)   { return x * 3; }
int        fake_impl(int x);   /* undefined — must not be linked */

#define USE_REAL 1

#define CRYPTO_DISPATCH(x) \
    __builtin_choose_expr(USE_REAL, real_impl(x), fake_impl(x))

static void test_macro_dispatch(void) {
    int r = CRYPTO_DISPATCH(7);
    CHECK("EC8: macro dispatch — only selected impl linked", r == 21);
}

/* ================================================================== *
 * EDGE CASE 9: Condition is a compound constant expression            *
 * involving bitwise arithmetic (common in crypto headers).           *
 * ================================================================== */
#define FEATURE_FLAGS 0x03u

static void test_bitwise_condition(void) {
    int r = __builtin_choose_expr(
                (FEATURE_FLAGS & 0x01u) != 0u,
                11,
                undefined_fn()
             );
    CHECK("EC9: bitwise constant condition", r == 11);

    int s = __builtin_choose_expr(
                (FEATURE_FLAGS & 0x04u) != 0u,
                undefined_fn(),
                22
             );
    CHECK("EC9: bitwise constant condition (false path)", s == 22);
}

/* ================================================================== *
 * EDGE CASE 10: __builtin_choose_expr as an initialiser in a         *
 * static / file-scope variable.                                      *
 *                                                                     *
 * Buggy chibicc: may refuse choose_expr outside function bodies,     *
 * or fail to constant-fold it for static initialisation.            *
 * ================================================================== */
static const int STATIC_VAL =
    __builtin_choose_expr(1, 0xAB, 0xCD);

static void test_static_initialiser(void) {
    CHECK("EC10: choose_expr as static initialiser", STATIC_VAL == 0xAB);
}

/* ================================================================== *
 * main                                                               *
 * ================================================================== */
int main(void) {
    puts("=== __builtin_choose_expr edge-case suite ===");
    test_unevaluated_branch_linkage();
    test_ill_typed_branch();
    test_lvalue_result();
    test_nested();
    test_sizeof_condition();
    test_constant_p_condition();
    test_type_preservation();
    test_macro_dispatch();
    test_bitwise_condition();
    test_static_initialiser();

    printf("\n%d passed, %d failed\n", g_pass, g_fail);
    return g_fail ? 1 : 0;
}

