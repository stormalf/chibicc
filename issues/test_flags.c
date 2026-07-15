#include "test.h"

// Test -ffreestanding: should not warn about missing standard library functions
// In freestanding environment, standard library functions may not be available
void* my_memcpy(void* dest, const void* src, size_t n) {
    char* d = dest;
    const char* s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

// Test -Wimplicit-function-declaration: should warn about implicit declarations
// We'll intentionally not declare a function to test the warning
int main() {
    // This should trigger -Wimplicit-function-declaration warning
    // because external_func is not declared
    int result = external_func();
    
    // Test -fvisibility=hidden: this is tested by compilation success
    // The flag affects symbol visibility in the output, which we can't easily test
    // in a simple C program, but we can verify it's accepted
    return result;
}
