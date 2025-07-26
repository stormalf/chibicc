#include <stdio.h>
#include <stdarg.h>
#include "test.h"

typedef struct { char g; } G;
typedef struct { float f; } F;

long double test_func(G g0, G g1, F f0, F f1, int i0, int i1, ...) {
    va_list ap;
    va_start(ap, i1);
    long double ret = i0 + i1;
    ret += va_arg(ap, long double);
    ret += va_arg(ap, int);
    ret += va_arg(ap, double);
    va_end(ap);
    return ret;
}

long double test_func1(G g0, G g1, F f0, F f1, int i0, int i1, ...) {
    va_list ap;
    va_start(ap, i1);
    long double ld = va_arg(ap, long double);
    va_end(ap);
    return ld;
}
double test_func2(G g0, G g1, F f0, F f1, int i0, int i1, ...) {
    va_list ap;
    va_start(ap, i1);
    double d = va_arg(ap, double);
    va_end(ap);
    return d;
}
int test_func3(G g0, G g1, F f0, F f1, int i0, int i1, ...) {
    va_list ap;
    va_start(ap, i1);
    int x = va_arg(ap, int);
    va_end(ap);
    return x;
}


int main() {
    G g0 = {10}, g1 = {11};
    F f0 = {20.0f}, f1 = {21.0f};
    long double ld = 2.5L;
    int i = 5;
    double d = 4.5;
    long double res1 = test_func1(g0, g1, f0, f1, 1, 2, ld);
    printf("Result: %Lf\n", res1);
    ASSERT(2, res1);
    double res2 = test_func2(g0, g1, f0, f1, 1, 2, d);
    printf("Result: %f\n", res2);    
    ASSERT(4, res2);
    int res3 = test_func3(g0, g1, f0, f1, 1, 2, i);
    printf("Result: %d\n", res3);    
    ASSERT(5, res3);

    long double res = test_func(g0, g1, f0, f1, 1, 2, ld, i, d);
    printf("Result: %Lf\n", res);
    ASSERT(15, res);
    return 0;
}
