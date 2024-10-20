#include <stdio.h>
#include "test.h"

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
        if (i == 0)
            ASSERT(1, arr[i]);
        else if (i == 1)
            ASSERT(2, arr[i]);
        else if (i == 2)    
            ASSERT(3, arr[i]);
        else if (i == 3)
            ASSERT(4, arr[i]);

    }
    return 0;
}
