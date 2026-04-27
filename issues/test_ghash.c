#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t OPENSSL_ia32cap_P[4] = {0, 0, 0, 0};

void gcm_ghash_4bit(uint64_t Xi[2], uint64_t H[16][2], const unsigned char *inp, size_t len);

void __attribute__((noinline)) caller(uint64_t Xi[2], uint64_t H[16][2], const unsigned char *inp, size_t len) {
    char padding[1];
    padding[0] = 0;
    gcm_ghash_4bit(Xi, H, inp, len);
    (void)padding;
}

int main() {
    uint64_t Xi[2] = {0};
    uint64_t H[16][2] = {0};
    unsigned char inp[16] = {0};
    
    printf("Calling gcm_ghash_4bit via caller...\n");
    caller(Xi, H, inp, 16);
    printf("Successfully returned.\n");
    
    return 0;
}
