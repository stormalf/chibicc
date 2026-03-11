#include <stdio.h>
#include <stdalign.h>

void callee(int n) {
    if (n > 0) callee(n - 1);
}

void caller(int n) {
    alignas(32) int x;
    (void)x;
    if (n > 0) callee(n - 1);
}

int main() {
    caller(10);
    printf("OK\n");
    return 0;
}
