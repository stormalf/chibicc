#include "test.h"
#include <stddef.h>
void *get_return_address() {
    return __builtin_return_address(0);
}

void *dummy_function() {
    return __builtin_return_address(0);
}

int main() {
    printf("Return address: %p\n", get_return_address());
    printf("Return function : %p\n", dummy_function());
    ASSERT(1, get_return_address() != NULL);
    ASSERT(1, dummy_function() != NULL);
    return 0;
}

