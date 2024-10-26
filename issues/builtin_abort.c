#include <stdio.h>

// Declare the __builtin_abort function
void __builtin_abort(void);

int main() {
    printf("Before aborting...\n");
    
    // Call __builtin_abort, which should terminate the program
    __builtin_abort();
    
    // This line should never be executed
    printf("This line should never be printed.\n");
    return 0;
}

