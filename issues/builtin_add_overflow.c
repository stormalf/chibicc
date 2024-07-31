
#include <stdio.h>


int main() {
    int result;
    if (__builtin_add_overflow(2147483647, 1, &result)) {
        printf("Overflow detected!\n");
    }
    return 0;
}
