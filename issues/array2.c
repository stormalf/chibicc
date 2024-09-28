#include <stdio.h>

void initialize_array(int arr[4]) {
    for (int i = 0; i < 4; i++) {
        arr[i] = i + 1; // Initialize array elements
    }
}

int main(void) {
    int arr[4];
    initialize_array(arr);
    for (int i = 0; i < 4; i++) {
        printf("arr[%d]: %d\n", i, arr[i]); // Expect 1, 2, 3, 4
    }
    return 0;
}
