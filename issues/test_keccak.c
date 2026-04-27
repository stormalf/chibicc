#include <stdio.h>
#include <stdint.h>
#include <string.h>

void SHA3_absorb(uint64_t A[5][5], const unsigned char *inp, size_t len, size_t r);

void __attribute__((noinline)) caller(uint64_t A[5][5], const unsigned char *inp, size_t len, size_t r) {
    char padding[1];
    padding[0] = 0;
    SHA3_absorb(A, inp, len, r);
    (void)padding;
}

int main() {
    uint64_t A[5][5] = {0};
    unsigned char inp[16] = {0};
    
    printf("Calling SHA3_absorb via caller...\n");
    caller(A, inp, 16, 136);
    printf("Successfully returned.\n");
    
    return 0;
}
