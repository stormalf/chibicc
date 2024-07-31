#include <stdio.h>

int main() {
    int value = 5;
    int old_value = __sync_val_compare_and_swap(&value, 5, 10);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 5, New value: 10
    return 0;
}

