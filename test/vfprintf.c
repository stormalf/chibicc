#define _GNU_SOURCE
#include "test.h"
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

/* Core vfprintf wrapper */
static void test_vfprintf(const char *fmt, ...)
{
    va_list ap;
    char buf[512];

    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);

    puts(buf);
}

/* Stress multiple argument types */
int main(void)
{
    puts("==== BASIC TYPES ====");
    test_vfprintf("int: %d\n", 42);
    test_vfprintf("unsigned: %u\n", 42u);
    test_vfprintf("hex: %x\n", 0xdeadbeef);
    test_vfprintf("octal: %o\n", 0777);
    test_vfprintf("char: %c\n", 'A');
    test_vfprintf("string: %s\n", "hello");

    puts("\n==== SIZE VARIANTS ====");
    test_vfprintf("short: %hd\n", (short)123);
    test_vfprintf("long: %ld\n", 1234567890L);
    test_vfprintf("long long: %lld\n", 1234567890123LL);
    test_vfprintf("size_t: %zu\n", (size_t)123456);
    test_vfprintf("ptrdiff_t: %td\n", (ptrdiff_t)-42);
    test_vfprintf("intptr_t: %jd\n", (intmax_t)9223372036854775807LL);

    puts("\n==== FLOATING POINT ====");
    test_vfprintf("float: %f\n", 3.1415926f);
    test_vfprintf("double: %lf\n", 2.718281828);
    test_vfprintf("scientific: %e\n", 1.23e+10);
    test_vfprintf("compact: %g\n", 12345.6789);

    puts("\n==== LONG DOUBLE ====");
    long double ld = 1.234567890123456789L;
    test_vfprintf("long double: %Lf\n", ld);

    puts("\n==== WIDTH / PRECISION ====");
    test_vfprintf("width: [%10d]\n", 123);
    test_vfprintf("left:  [%-10d]\n", 123);
    test_vfprintf("prec:  [%.5d]\n", 123);
    test_vfprintf("mix:   [%10.5d]\n", 123);

    puts("\n==== STAR WIDTH / PRECISION ====");
    test_vfprintf("star width: [%*d]\n", 8, 42);
    test_vfprintf("star prec:  [%.*f]\n", 3, 3.1415926);
    test_vfprintf("both:       [%*.*f]\n", 8, 3, 3.1415926);

    puts("\n==== POINTERS ====");
    int x = 123;
    test_vfprintf("pointer: %p\n", (void *)&x);

    puts("\n==== MIXED ARGUMENT ORDER ====");
    test_vfprintf("mix: %d %f %s %ld %c\n", 7, 1.5, "txt", 9999999L, 'Z');

    puts("\n==== REPEATED VARARGS ====");
    test_vfprintf("%d %d %d %d %d\n", 1, 2, 3, 4, 5);

    puts("\n==== DONE ====");
    return 0;
}
