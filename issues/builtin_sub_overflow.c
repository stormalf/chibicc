#include <stdio.h>
int main() {
    int result;
    if (__builtin_sub_overflow(-2147483648, 1, &result)) {
        printf("Overflow detected!\n");
    }
    return 0;
}

