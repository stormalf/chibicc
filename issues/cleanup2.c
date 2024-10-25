#include <stdio.h>

#define call_cleaner(cleaner) __attribute__((__cleanup__(cleaner##_function))) __attribute__((unused))
#define __do_close(cleaner) call_cleaner(cleaner) // Redirect to call_cleaner

// Cleanup function
// void my_cleanup_function(int *ptr) {
//     // if (ptr) { // Check if the pointer is valid
//     //     printf("Cleaning up: %d\n", *ptr);
//     // } else {
//         printf("Cleaning up: NULL pointer\n");
//     // }
// }
// Cleanup function
void my_cleanup_function() {
    // if (ptr) { // Check if the pointer is valid
    //     printf("Cleaning up: %p\n", *ptr);
    // } else {
        printf("Cleaning up: NULL pointer\n");
    // }
}


// Function to test the cleanup
void test_cleanup() {
    // Declare a variable with the __do_close macro
    __do_close(my_cleanup) int my_var = 42;

    // Use the variable
    printf("Inside test_cleanup: my_var = %d\n", my_var);
}

int main() {
    printf("Starting main function\n");
    
    test_cleanup(); // Call the function that uses the cleanup

    printf("Exiting main function\n");
    return 0;
}
