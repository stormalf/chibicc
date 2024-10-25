#include <stdio.h>

void my_cleanup() {
    printf("Cleanup function called.\n");
}

int main() {
    __attribute__((cleanup(my_cleanup)))  int my_var;
    my_var = 42; // No initialization needed for the test
    printf("Inside main function.\n");
    return 0;
}
