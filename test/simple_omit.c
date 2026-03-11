#include <stdio.h>

void f(int n) {
    if (n > 0) f(n - 1);
}

int main() {
    f(10);
    return 0;
}
