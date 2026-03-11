#include <stdio.h>

void f(int depth) {
    char buf[64]; // stack allocation
    printf("%p\n", (void*)&buf);
    if (depth < 10) f(depth+1);
}

int main() {
    f(0);
}

