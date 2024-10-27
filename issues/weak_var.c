#include <stdio.h>

// Define the original variable
int original_var = 100;

// Declare the alias with extern
extern int alias_var __attribute__((weak, alias("original_var")));
int non_weak_var = 10;

int main() {
    printf("Value of original_var: %d\n", original_var);
    printf("Value of alias_var: %d\n", alias_var);

    // Modify 'alias_var' and see the effect on 'original_var'
    alias_var = 200;
    printf("After modification:\n");
    printf("Value of original_var: %d\n", original_var);
    printf("Value of alias_var: %d\n", alias_var);

    return 0;
}
