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
    int a = va_arg(ap, int);
    printf("a=%d\n", a);
    ASSERT(17, a);
    int b = va_arg(ap, int);
    printf("b=%d\n", b);
    ASSERT(23, b);
    int c = va_arg(ap, int);
    printf("c=%d\n", b);
    ASSERT(19, c);    
    double f = va_arg(ap, double);
    printf("f=%lf\n", f);
    ASSERT(10, f);    
    long double ld = va_arg(ap, long double);
    printf("ld=%Ld\n", ld);
    ASSERT(25, ld);            
    for (int i = 0; i < count - 5 ; i++) {
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
    int a = 17;
    int b = 23;
    int c = 19;
    float f = 10.50;
    long double ld = 25.50L;    
    print7(13, a, b, c, f, ld,  s1, s2, s3, s4, s5, s6, s7, s8);
    return 0;
}
