#include <stdio.h>
int main() {
    char buffer[10];
    __builtin_memset(buffer, 'A', sizeof(buffer));
    for (int i = 0; i < 10; i++) {
        putchar(buffer[i]);
    }
    putchar('\n');
    return 0;
}
