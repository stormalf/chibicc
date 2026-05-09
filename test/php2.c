#include "test.h"
#include <stdint.h>

typedef long zend_long;
typedef double zend_double;

/* Mock of PHP zval struct */
typedef struct {
    zend_long lval;
    zend_double dval;
} zval;

/* Mock access macros */
#define Z_LVAL_P(z) ((z)->lval)
#define Z_DVAL_P(z) ((z)->dval)

int main(void) {
    zval _op1 = {123456789, 0.0};
    zval _op2 = {987654321, 0.0};
    zval _result = {0, 0.0};
    int overflow = 0;

    /* Pointers to simulate real PHP usage */
    zval *op1 = &_op1;
    zval *op2 = &_op2;
    zval *result = &_result;

    /* x86-64 version of ZEND_SIGNED_MULTIPLY_LONG */
#define ZEND_SIGNED_MULTIPLY_LONG(a, b, lval, dval, usedval) do { \
    zend_long __tmpvar;                                           \
    __asm__ ("imul %3,%0\n"                                       \
             "adc $0,%1"                                          \
             : "=r"(__tmpvar), "=r"(usedval)                     \
             : "0"(a), "r"(b), "1"(0));                          \
    if (usedval) (dval) = (double) (a) * (double) (b);           \
    else (lval) = __tmpvar;                                       \
} while (0)

    /* Perform the multiplication as PHP does */
    ZEND_SIGNED_MULTIPLY_LONG(Z_LVAL_P(op1), Z_LVAL_P(op2),
                              Z_LVAL_P(result), Z_DVAL_P(result),
                              overflow);

    /* Print result */
    if (overflow)
        printf("Overflow detected, double result: %f\n", Z_DVAL_P(result));
    else
        printf("Result fits in long: %ld\n", Z_LVAL_P(result));
    ASSERT(0, overflow);
    ASSERT(121932631112635269, Z_LVAL_P(result));
    return 0;
}
