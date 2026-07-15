#include <stdarg.h>
#include <stdio.h>

typedef struct {
    int a;
    double b;
} MediumStruct;

void print_medium(int n, ...) {
    va_list ap;
    va_start(ap, n);
    MediumStruct s = va_arg(ap, MediumStruct);
    printf("a = %d, b = %f\n", s.a, s.b);
    va_end(ap);
}

int main() {
    MediumStruct s = {1, 1.1};
    print_medium(1, s);
    return 0;
}
