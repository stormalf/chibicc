// This program is designed to test some arm64-specific things, such as the
// calling convention, but should give the same results on any architecture.

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include "test.h"


struct hfa21 { double a; } hfa21 = { 21.1 };
struct hfa22 { double a, b; } hfa22 = { 22.1, 22.2 };
struct hfa23 { double a, b, c; } hfa23 = { 23.1, 23.2, 23.3 };
struct hfa24 { double a, b, c, d; } hfa24 = { 24.1, 24.2, 24.3, 24.4 };

struct hfa31 { long double a; } hfa31 = { 31.1 };
struct hfa32 { long double a, b; } hfa32 = { 32.1, 32.2 };
struct hfa33 { long double a, b, c; } hfa33 = { 33.1, 33.2, 33.3 };
struct hfa34 { long double a, b, c, d; } hfa34 = { 34.1, 34.2, 34.3, 34.4 };


int match(const char **s, const char *f)
{
    const char *p = *s;
    for (p = *s; *f && *f == *p; f++, p++)
        ;
    if (!*f) {
        *s = p - 1;
        return 1;
    }
    return 0;
}


void myprintf(const char *format, ...)
{
    const char *s;
    va_list ap;
    va_start(ap, format);
    for (s = format; *s; s++) {
        if (match(&s, "%hfa21")) {
            struct hfa21 x = va_arg(ap, struct hfa21);
            printf("%.1f,%.1f", x.a, x.a);
        }
        else if (match(&s, "%hfa22")) {
            struct hfa22 x = va_arg(ap, struct hfa22);
            printf("%.1f,%.1f", x.a, x.b);
        }
        else if (match(&s, "%hfa23")) {
            struct hfa23 x = va_arg(ap, struct hfa23);
            printf("%.1f,%.1f", x.a, x.c);
        }
        else if (match(&s, "%hfa24")) {
            struct hfa24 x = va_arg(ap, struct hfa24);
            printf("%.1f,%.1f", x.a, x.d);
        }
        else if (match(&s, "%hfa31")) {
            struct hfa31 x = va_arg(ap, struct hfa31);
            printf("%.1Lf,%.1Lf", x.a, x.a);
        }
        else if (match(&s, "%hfa32")) {
            struct hfa32 x = va_arg(ap, struct hfa32);
            printf("%.1Lf,%.1Lf", x.a, x.b);
        }
        else if (match(&s, "%hfa33")) {
            struct hfa33 x = va_arg(ap, struct hfa33);
            printf("%.1Lf,%.1Lf", x.a, x.c);
        }
        else if (match(&s, "%hfa34")) {
            struct hfa34 x = va_arg(ap, struct hfa34);
            printf("%.1Lf,%.1Lf", x.a, x.d);
        }
        else
            putchar(*s);
    }
    putchar('\n');
}

int main()
{

    printf("stdarg:\n");
    myprintf("%hfa24 %hfa22 %hfa21 %hfa21 %hfa21 %hfa21",
             hfa24, hfa22, hfa21, hfa21, hfa21, hfa21);

    return 0;
}