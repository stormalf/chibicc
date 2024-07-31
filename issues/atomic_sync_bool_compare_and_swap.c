#include <stdio.h>

int main() {
    int value = 5;
    int result = __sync_bool_compare_and_swap(&value, 5, 10);
    printf("Compare and swap result: %d, New value: %d\n", result, value); // Result: 1, New value: 10
    return 0;
}

