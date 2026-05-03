#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t OPENSSL_ia32cap_P[4] = {0, 0, 0, 0};

void gcm_gmult_4bit(uint64_t Xi[2], uint64_t H[16][2]);

void __attribute__((noinline)) caller(uint64_t Xi[2], uint64_t H[16][2]) {
    char padding[1];
    padding[0] = 0;
    gcm_gmult_4bit(Xi, H);
    (void)padding;
}

int main() {
    uint64_t Xi[2] = {0};
    uint64_t H[16][2] = {0};
    
    printf("Calling gcm_gmult_4bit via caller...\n");
    caller(Xi, H);
    printf("Successfully returned.\n");
    
    return 0;
}