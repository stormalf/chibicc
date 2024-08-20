#include <stdio.h>
#include <stdlib.h>

#define MEM_SIZE 100 // Define the size of the memory block

void printMemoryStatus(char *memory, int size);

int main() {
    char *memory = (char *)malloc(MEM_SIZE * sizeof(char)); // Allocate memory block
    if (memory == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1;
    }

    // Initially, mark all memory as free
    for (int i = 0; i < MEM_SIZE; ++i) {
        memory[i] = 'F';
    }

    // Example usage: Allocating memory at address 10 to 20
    for (int i = 10; i < 20; ++i) {
        memory[i] = '*';
    }

    // Print the memory status
    printMemoryStatus(memory, MEM_SIZE);

    // Freeing memory at address 10 to 20
    for (int i = 10; i < 20; ++i) {
        memory[i] = 'F';
    }

    // Print the memory status after freeing memory
    printMemoryStatus(memory, MEM_SIZE);

    // Free dynamically allocated memory
    free(memory);

    return 0;
}

// Function to print memory status
void printMemoryStatus(char *memory, int size) {
    printf("Memory Status:\n");
    for (int i = 0; i < size; ++i) {
        printf("%c ", memory[i]);
    }
    printf("\n");
}
