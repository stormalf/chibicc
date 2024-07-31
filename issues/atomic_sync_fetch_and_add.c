#include <stdio.h>

int main() {
    int value = 5;
    int old_value = __sync_fetch_and_add(&value, 3);
    printf("Old value: %d, New value: %d\n", old_value, value); // Old value: 5, New value: 8
    return 0;
}

