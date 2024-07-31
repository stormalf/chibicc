#include <stdio.h>
void *get_return_address() {
    return __builtin_return_address(0);
}

int main() {
    printf("Return address: %p\n", get_return_address());
    return 0;
}

