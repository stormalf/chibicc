#include <stdio.h>
#include <string.h>

// Define the functions with the required signatures
void pgstat_archiver_init_shmem_cb(void *stats) {
    printf("Archiver init_shmem_cb called with %p\n", stats);
}

// Define a struct with two function pointers
struct MyStruct {
    void (*copy_func)(void *dest, const void *src, size_t n); // Function like memcpy
    void (*init_shmem_cb)(void *stats);                       // Function for initializing shared memory
};

// Initialize a static const array of MyStruct with two elements
static const struct MyStruct myArray[2] = {
    [0] = {
        .copy_func = memcpy, // Only initialize the first function
        // init_shmem_cb is not initialized
    },
    [1] = {
        // copy_func is not initialized
        .init_shmem_cb = pgstat_archiver_init_shmem_cb, // Only initialize the second function
    }
};

int main() {
    char src[] = "Hello, world!";
    char dest[50];
    void *dummyStats = (void *)0x1234;  // Some dummy stats pointer

    // Loop through the array and call the appropriate function
    for (int i = 0; i < 2; i++) {
        if (myArray[i].copy_func) {
            // Call the first function if it's initialized
            myArray[i].copy_func(dest, src, sizeof(src));
            printf("Array element %d - Copy result: %s\n", i + 1, dest);
        } else if (myArray[i].init_shmem_cb) {
            // Call the second function if it's initialized
            myArray[i].init_shmem_cb(dummyStats);
            printf("Array element %d - Called init_shmem_cb\n", i + 1);
        } else {
            printf("Array element %d - No function initialized\n", i + 1);
        }
    }

    return 0;
}
