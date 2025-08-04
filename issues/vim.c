#include <stdio.h>

int main() {
    int x = (0 < 2 || 0) ? -1 : 42;
    printf("%d\n", x); // Should print -1
    return 0;
}
