#include <stdio.h>

int main() {
    int value = 5;
    int old_value = __sync_fetch_and_sub(&value, 2);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 5, New value: 3
    return 0;
}

