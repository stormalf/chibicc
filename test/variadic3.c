#include <stddef.h>
#include <stdarg.h>
#include "test.h"

typedef struct {
    long double ld;
} MyStruct;

void print_variadic(int count, ...) {
    va_list ap;
    va_start(ap, count);

    for (int i = 0; i < count; i++) {
        MyStruct s = va_arg(ap, MyStruct);
        printf("MyStruct[%d].ld = %Lf\n", i, s.ld);
        if (i == 0)
            ASSERT(1, s.ld);
        else if (i == 1)
            ASSERT(9, s.ld);
    }

    va_end(ap);
}

int main(void) {
    MyStruct a = {1.234567890123456789L};
    MyStruct b = {9.876543210987654321L};

    print_variadic(2, a, b);
    return 0;
}
