#include <stddef.h>
#include <stdarg.h>
#include "test.h"

typedef struct S {
    _Alignas(32)
    char data[32];
} S;

void print7(int count, ...) {
    va_list ap;
    va_start(ap, count);

    for (int i = 0; i < count; i++) {
        S s = va_arg(ap, S);
        printf("%d ", s.data[0]);
        ASSERT(i + 1, s.data[0]);
    }

    va_end(ap);
    printf("\n");
}

int main() {
    S s1 = {.data = {1}};
    S s2 = {.data = {2}};
    S s3 = {.data = {3}};
    S s4 = {.data = {4}};
    S s5 = {.data = {5}};
    S s6 = {.data = {6}};
    S s7 = {.data = {7}};
    S s8 = {.data = {8}};

    print7(8, s1, s2, s3, s4, s5, s6, s7, s8);
    return 0;
}
