#include <stdio.h>

int main() {
    unsigned int x = 0x80000000;
    unsigned long y = x;
    printf("x = 0x%x, y = 0x%lx\n", x, y);
    if (y != 0x80000000UL) {
        printf("BUG: y is incorrectly extended!\n");
    } else {
        printf("y is correctly extended.\n");
    }
    return 0;
}
