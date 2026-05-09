// va_copy_test.c
#include <stdio.h>
#include <stdarg.h>

static int sum(int n, ...) {
    va_list ap, ap2;
    va_start(ap, n);
    va_copy(ap2, ap);

    int s1 = 0, s2 = 0;
    for (int i = 0; i < n; i++)
        s1 += va_arg(ap, int);
    for (int i = 0; i < n; i++)
        s2 += va_arg(ap2, int);

    va_end(ap);
    va_end(ap2);
    return s1 + s2;
}

int main(void) {
    printf("%d\n", sum(4, 1, 2, 3, 4)); // expected 20
}
