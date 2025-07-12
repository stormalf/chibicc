#include <stdio.h>
#include <stdarg.h>
#include "test.h"

void test_variadic(double first_named, int count, ...) {
    printf("named arg = %f\n", first_named);

    va_list ap;
    va_start(ap, count);

    for (int i = 0; i < count; i++) {
        double val = va_arg(ap, double);
        printf("variadic arg[%d] = %f\n", i, val);
        if (i == 15)
            ASSERT(15, val );
    }

    va_end(ap);
}

int main() {
    test_variadic(
        0.0, 15,
        1.1, 2.2, 3.3, 4.4,
        5.5, 6.6, 7.7, 8.8,
        9.9, 10.10, 11.11, 12.12,
        13.13, 14.14, 15.15
    );
    return 0;
}
