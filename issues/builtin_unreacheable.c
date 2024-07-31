#include <stdio.h>
int main() {
    int x = 0;
    if (x == 0) {
        printf("x is zero\n");
    } else {
        __builtin_unreachable();
    }
    return 0;
}

