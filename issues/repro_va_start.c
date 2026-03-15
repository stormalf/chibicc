#include <stdarg.h>
#include <stdio.h>

void test_va(int i, ...) {
    va_list ap;
    int actual = (va_start(ap, i), 123);
    printf("actual = %d\n", actual);
}

int main() {
    test_va(0, 1);
    return 0;
}
