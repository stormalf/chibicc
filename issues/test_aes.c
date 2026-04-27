#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t OPENSSL_ia32cap_P[4] = {0, 0, 0, 0};

void AES_encrypt(const unsigned char *in, unsigned char *out, const void *key);

void __attribute__((noinline)) caller(const unsigned char *in, unsigned char *out, const void *key) {
    char padding[1];
    padding[0] = 0;
    AES_encrypt(in, out, key);
    (void)padding;
}

int main() {
    unsigned char in[16] = {0};
    unsigned char out[16] = {0};
    uint32_t key[64] = {0}; 
    key[60] = 10; // rounds at offset 240 (60 * 4)
    
    printf("Calling AES_encrypt via caller...\n");
    caller(in, out, key);
    printf("Successfully returned.\n");
    
    return 0;
}
