#include <stdio.h>

void print_frame_addresses(const char *label) {
    void *f0 = __builtin_frame_address(0);
    void *f1 = __builtin_frame_address(1);
    void *f2 = __builtin_frame_address(2);
    printf("%s f0 = %p\n", label, f0);
    printf("%s f1 = %p\n", label, f1);
    printf("%s f2 = %p\n", label, f2);
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
