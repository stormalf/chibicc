#include <stdio.h>
#include <stdarg.h>
#include "test.h"

long double add_int_ld_variadic(int count, ...) {
    va_list ap;
    va_start(ap, count);

    int a = va_arg(ap, int);
    long double b = va_arg(ap, long double);

    va_end(ap);

    return a + b;
}

int main() {
    int x = 100;
    long double y = 10.5;

    long double result = add_int_ld_variadic(2, x, y);

    printf("Result = %.2Lf\n", result);
    ASSERT(110.5, result);
    // Expected: 110.50

    return 0;
}
