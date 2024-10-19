#include <stdio.h>

// Function prototype: x is treated as an array of pointers to const int
void foovm(int x[const *]); 

int main() {
    int a = 10, b = 20, c = 30;
    int *arr[] = { &a, &b, &c }; // Array of pointers to int

    // Call the function with the array of pointers
    foovm(arr);

    return 0;
}

void foovm(int x[const 8]) {  // Adjusted definition
    // Accessing the values via the array of pointers
    for (int i = 0; i < 3; i++) {
        // Dereferencing to get the value
        printf("Value %d: %p\n", i + 1, x[i]);
    }

    // Attempting to modify the pointers (not allowed)
    // x[0] = NULL; // This would cause a compile-time error
}