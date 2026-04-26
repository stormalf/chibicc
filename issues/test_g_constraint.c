#include <stdio.h>
#include <openssl/bn.h>

/*
 * Simplified replacement for TEST_error / TEST_BN_eq
 * so we can run standalone.
 */
static void TEST_error(const char *msg, const char *op)
{
    printf("ERROR: ");
    printf(msg, op);
    printf("\n");
}

static int TEST_BN_eq(const BIGNUM *a, const BIGNUM *b)
{
    char *as = BN_bn2hex(a);
    char *bs = BN_bn2hex(b);

    printf("expected: %s\n", as);
    printf("actual:   %s\n", bs);

    OPENSSL_free(as);
    OPENSSL_free(bs);
    return 0;
}

/*
 * Your function under test
 */
static int equalBN(const char *op, const BIGNUM *expected, const BIGNUM *actual)
{
    if (BN_cmp(expected, actual) == 0)
        return 1;

    TEST_error("unexpected %s value", op);
    TEST_BN_eq(expected, actual);
    return 0;
}

int main(void)
{
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *c = BN_new();

    /*
     * Case 1: equal values → must pass BN_cmp path
     */
    BN_set_word(a, 12345);
    BN_set_word(b, 12345);

    printf("== CASE 1 (should PASS)\n");
    if (!equalBN("test1", a, b)) {
        printf("FAIL CASE 1\n");
    }

    /*
     * Case 2: different values → must trigger TEST_BN_eq
     */
    BN_set_word(c, 54321);

    printf("\n== CASE 2 (should FAIL)\n");
    if (!equalBN("test2", a, c)) {
        printf("FAIL CASE 2 (expected)\n");
    }

    BN_free(a);
    BN_free(b);
    BN_free(c);
    BN_CTX_free(ctx);

    return 0;
}
