// Test __attribute__((noreturn))
#include "test.h"

int called;

__attribute__((noreturn)) void my_exit(void) {
    called = 1;
    while(1) {}
}

int main() {
    // We can't actually call my_exit() and return, but we can test
    // that noreturn attribute compiles and links correctly.
    // Just test that the function pointer can be formed.
    void (*fp)(void) = my_exit;
    ASSERT(1, called == 0);
    printf("OK\n");
    return 0;
}
