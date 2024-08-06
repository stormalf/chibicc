
#include <stdio.h>


int main() {
    int result;
    if (__builtin_add_overflow(54, 1, &result)) {
        printf("Overflow detected!\n");
    } else { 
        printf("Overflow not detected!\n");
    }
    printf("second test\n");
    if (__builtin_add_overflow(2147483647, 1, &result)) {
        printf("Overflow detected!\n");
    }


    return 0;
}
