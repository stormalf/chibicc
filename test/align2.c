//#include <stdio.h>
#include <stdarg.h>
#include "test.h"

struct __attribute__((aligned(128))) big128 {
    char buf[128];
};

struct __attribute__((aligned(1024))) big1024 {
    char buf[1024];
};

void test_big_align(int named_int, struct big128 s128, struct big1024 s1024, int count, ...) {
    printf("named int = %d\n", named_int);
    ASSERT(42, named_int);
    printf("struct big128 align = %zu size = %zu\n", __alignof__(s128), sizeof(s128));
    ASSERT(128, sizeof(s128) );
    printf("struct big1024 align = %zu size = %zu\n", __alignof__(s1024), sizeof(s1024));
    ASSERT(1024, sizeof(s1024));

    va_list ap;
    va_start(ap, count);

    for (int i = 0; i < count - 1 ; i++) {
        double val = va_arg(ap, double);
        printf("variadic double[%d] = %f\n", i, val);
        ASSERT(i+1, val);
    }
    struct big1024 s1024b = va_arg(ap, struct big1024);
    printf("struct big1024 align = %zu size = %zu\n", __alignof__(s1024b), sizeof(s1024b));
    ASSERT(1024, sizeof(s1024b));
    va_end(ap);
}

int main() {
    struct big128 s128 = {0};
    struct big1024 s1024 = {0};

    test_big_align(
        42,       // named int
        s128,     // struct with align 128
        s1024,    // struct with align 1024
        6,        // count

        // variadic doubles
        1.1, 2.2, 3.3, 4.4, 5.5, s1024
    );

    return 0;
}
