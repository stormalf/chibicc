#include "test.h"
#include <stdbool.h>

void print_frame_addresses(const char *label) {
    void *f0 = __builtin_frame_address(0);
    void *f1 = __builtin_frame_address(1);
    void *f2 = __builtin_frame_address(2);
    bool x = false;
    printf("%s f0 = %p\n", label, f0);
    x = f0;
    ASSERT(1, x);
    printf("%s f1 = %p\n", label, f1);
    x = f1;
    ASSERT(1, x);
    printf("%s f2 = %p\n", label, f2);
    x = f2;
    ASSERT(1, x);
}

void inner() {
    print_frame_addresses("inner");
}

void outer() {
    print_frame_addresses("outer-before");
    inner();
    print_frame_addresses("outer-after");
}

int main() {
    print_frame_addresses("main-before");
    outer();
    print_frame_addresses("main-after");
}