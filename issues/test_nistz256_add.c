#include <stdio.h>
#include <stdint.h>
#include <string.h>

void ecp_nistz256_point_add(uint64_t res[12], uint64_t a[12], uint64_t b[12]);

void __attribute__((noinline)) caller(uint64_t res[12], uint64_t a[12], uint64_t b[12]) {
    char padding[1];
    padding[0] = 0;
    ecp_nistz256_point_add(res, a, b);
    (void)padding;
}

int main() {
    uint64_t res[12], a[12] = {0}, b[12] = {0};
    
    printf("Calling ecp_nistz256_point_add via caller...\n");
    caller(res, a, b);
    printf("Successfully returned.\n");
    
    return 0;
}