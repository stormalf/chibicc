#include <stdio.h>
#include <stdint.h>

void callee(int *p) {
    if (p) *p = 42;
}

void caller(int n) {
    int x;
    callee(&x); // Address taken!
    if (n > 0) caller(n - 1);
}

int main() {
    caller(10);
    printf("OK\n");
    return 0;
}
