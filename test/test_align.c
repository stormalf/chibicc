#include <stdio.h>
#include <stddef.h>

int x __attribute__((aligned(64)));
int y;

int main() {
    printf("alignof(x) = %zu\n", _Alignof(x));
    printf("alignof(y) = %zu\n", _Alignof(y));
    if (_Alignof(y) == 64) {
        printf("BUG: y is aligned to 64!\n");
        return 1;
    }
    printf("OK\n");
    return 0;
}
