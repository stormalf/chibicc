#include <stdio.h>
#include <limits.h>
#include <float.h>
#include "test.h"

// Declare the variadic function (simulating curl_msprintf or dprintf_format)
// Simulated curl-style dprintf_format
int dprintf_format(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int ret = vprintf(fmt, ap);  // You can replace this with vsnprintf if needed
    va_end(ap);
    return ret;
}

int main(void) {
    char c = -1;
    unsigned char uc = 255;
    short s = -12345;
    unsigned short us = 54321;
    int i = -123456;
    unsigned int ui = 123456;
    long l = -123456789;
    unsigned long ul = 123456789;
    long long ll = -123456789012345;
    unsigned long long ull = 123456789012345;
    float f = 1.25f;
    double d = 3.14159;

    // Pass all the above to your variadic dprintf_format
    int n = dprintf_format(
        "char: %hhd\n"
        "unsigned char: %hhu\n"
        "short: %hd\n"
        "unsigned short: %hu\n"
        "int: %d\n"
        "unsigned int: %u\n"
        "long: %ld\n"
        "unsigned long: %lu\n"
        "long long: %lld\n"
        "unsigned long long: %llu\n"
        "float: %f\n"
        "double: %f\n",
        c, uc, s, us, i, ui, l, ul, ll, ull, f, d);

    printf("Printed %d characters\n", n);
    ASSERT(-1, c);
    ASSERT(255, uc);
    ASSERT(-12345, s);
    ASSERT(54321, us);
    ASSERT(-123456, i);
    ASSERT(123456, ui);
    ASSERT(-123456789, l);
    ASSERT(123456789, ul);
    ASSERT(-123456789012345LL, ll);
    ASSERT(123456789012345ULL, ull);
    ASSERT(1.25f, f);
    ASSERT(3.14159, d);

    printf("All tests passed!\n");
    return 0;
}
