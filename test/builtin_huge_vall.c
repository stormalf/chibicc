#include <stdio.h>
long double f() { return __builtin_huge_vall(); }

int main() {
    long double f1 = f();
    printf("%Lf\n", f1);

    return 0;
}