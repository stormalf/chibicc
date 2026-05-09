#include <stdarg.h>
#include "test.h"

void test_va(int i, ...) {
    va_list ap;
    int actual = (va_start(ap, i), 123);
    printf("actual = %d\n", actual);
    ASSERT(123, actual);
}

int main() {
    test_va(0, 1);

    printf("Ok\n");
    return 0;
}
