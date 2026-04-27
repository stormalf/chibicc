#include <stdio.h>
#include <stdint.h>
#include <string.h>

void ecp_nistz256_point_double(uint64_t res[12], uint64_t a[12]);

void __attribute__((noinline)) caller(uint64_t res[12], uint64_t a[12]) {
    char padding[1];
    padding[0] = 0;
    __attribute__((aligned(1))) char g = 'b';
    ecp_nistz256_point_double(res, a);
    (void)padding;
}

int main() {
    char x = 'a';
    uint64_t a[12] __attribute__((aligned(16))) = {0};
    int y = 15;
    uint64_t res[12] __attribute__((aligned(16))) = {0};
    __attribute__((aligned(8))) int z = 14;
    
    printf("Calling ecp_nistz256_point_double via caller...\n");
    caller(res, a);
    printf("Successfully returned.\n");
    
    return 0;
}
