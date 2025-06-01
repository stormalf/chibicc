#include <stdio.h>
float f() { return __builtin_huge_valf(); }

int main() {
    float f1 = f();
    printf("%f\n", f1);

    return 0;
}