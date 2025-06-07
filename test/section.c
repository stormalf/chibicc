#include <stdio.h>

__attribute__((section(".PyRuntime2"))) int test_var2  = 42;
int test_var __attribute__((section(".PyRuntime"))) = 42;

__attribute__((section(".my_custom_section")))
void test_section(void) {
    printf("Hello from .my_custom_section\n");
}

int main() {
    test_section();
    return 0;
}
