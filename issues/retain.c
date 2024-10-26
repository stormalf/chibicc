#include <stdio.h>

// Declare an integer variable that must not be optimized away
int xyzzy __attribute__((__used__, __retain__));

void initialize_variable() {
    xyzzy = 42; // Initialize the variable
}

int get_value() {
    return xyzzy; // Return the value of the variable
}

int main() {
    initialize_variable(); // Set the value of xyzzy
    printf("Value of xyzzy: %d\n", get_value()); // Print the value

    return 0;
}

