#include <stdio.h>
#include <stdarg.h>
#include "test.h"

void test_variadic(int named_int, double named_double, long double named_longdouble, int count, ...) {
    printf("named int = %d\n", named_int);
    printf("named double = %f\n", named_double);
    printf("named long double = %Lf\n", named_longdouble);

    va_list ap;
    va_start(ap, count);

    int v_int = va_arg(ap, int);
    printf("variadic int = %d\n", v_int);
    ASSERT(11, v_int);

    double v_double = va_arg(ap, double);
    printf("variadic double = %f\n", v_double);
    ASSERT(6, v_double);

    long double v_longdouble = va_arg(ap, long double);
    printf("variadic long double = %Lf\n", v_longdouble);
    ASSERT(1, v_longdouble);

    for (int i = 0; i < count; i++) {
        double val = va_arg(ap, double);
        printf("variadic extra double[%d] = %f\n", i, val);
    }

    va_end(ap);
}

int main() {
    test_variadic(
        42,                   // named int
        3.14159,              // named double
        2.718281828459,       // named long double
        10,                   // count of extra doubles

        // Variadic arguments
        11,                   // variadic int
        6.62607015,           // variadic double
        1.61803398875L,       // variadic long double

        // 10 extra variadic doubles
        10.10, 20.20, 30.30, 40.40, 50.50,
        60.60, 70.70, 80.80, 90.90, 100.100
    );

    return 0;
}
