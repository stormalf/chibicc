
#include "test.h"

void test_non_variadic(
    int a1,
    long double a2,
    double a3,
    long double a4,
    double a5,
    long double a6,
    double a7,
    int a8,
    double a9,
    long double a10,
    double a11,
    long double a12,
    double a13,
    long double a14,
    double a15,
    double a16
) {
    printf("a1 (int) = %d\n", a1);
    ASSERT(1, a1);
    printf("a2 (long double) = %Lf\n", a2);
    ASSERT(2, a2);
    printf("a3 (double) = %f\n", a3);
    ASSERT(3, a3);
    printf("a4 (long double) = %Lf\n", a4);
    ASSERT(4, a4);
    printf("a5 (double) = %f\n", a5);
    ASSERT(5, a5);
    printf("a6 (long double) = %Lf\n", a6);
    ASSERT(6, a6);
    printf("a7 (double) = %f\n", a7);
    ASSERT(7, a7);
    printf("a8 (int) = %d\n", a8);
    ASSERT(8, a8);
    printf("a9 (double) = %f\n", a9);
    ASSERT(9, a9);
    printf("a10 (long double) = %Lf\n", a10);
    ASSERT(10, a10);
    printf("a11 (double) = %f\n", a11);
    ASSERT(11, a11);
    printf("a12 (long double) = %Lf\n", a12);
    ASSERT(12, a12);
    printf("a13 (double) = %f\n", a13);
    ASSERT(13, a13);
    printf("a14 (long double) = %Lf\n", a14);
    ASSERT(14, a14);
    printf("a15 (double) = %f\n", a15);
    ASSERT(15, a15);
    printf("a16 (double) = %f\n", a16);
    ASSERT(16, a16);
}

int main() {
    test_non_variadic(
        1,                              // int
        2.222222222222L,                // long double
        3.333333,                      // double
        4.444444444444L,                // long double
        5.555555,                      // double
        6.666666666666L,                // long double
        7.777777,                      // double
        8,                              // int
        9.999999,                      // double
        10.101010101010L,               // long double
        11.111111,                     // double
        12.121212121212L,               // long double
        13.131313,                     // double
        14.141414141414L,               // long double
        15.151515,                     // double
        16.161616                      // double
    );
    return 0;
}
