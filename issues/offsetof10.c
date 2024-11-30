#include <stdio.h>
#include <stdlib.h>
#include <stddef.h> // For offsetof

struct Example {
    int size;    // Number of elements in the flexible array
    int data[];  // Flexible array member
};

int main() {
    int n = 5;  // Number of integers to allocate in the flexible array

    // Calculate the total size required for the struct and the flexible array
    size_t total_size = offsetof(struct Example, data) + n * sizeof(int);

    // Allocate memory for the struct including space for n integers
    struct Example *ex = malloc(total_size);
    if (!ex) {
        perror("Failed to allocate memory");
        return 1;
    }

    // Set the size
    ex->size = n;

    // Initialize the flexible array
    for (int i = 0; i < n; i++) {
        ex->data[i] = i * 10;  // Fill with some values (0, 10, 20, ...)
    }

    // Perform some actions on the struct
    printf("Size: %d\n", ex->size);
    printf("Data: ");
    for (int i = 0; i < ex->size; i++) {
        printf("%d ", ex->data[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(ex);

    return 0;
}
