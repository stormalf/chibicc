#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t OPENSSL_ia32cap_P[4] = {0, 0, 0, 0};

void sha256_block_data_order(uint32_t *state, const void *data, size_t num_blocks);

void __attribute__((noinline)) caller(uint32_t *state, const void *data, size_t num_blocks) {
    char padding[1];
    padding[0] = 0;
    sha256_block_data_order(state, data, num_blocks);
    (void)padding;
}

int main() {
    uint32_t state[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
    unsigned char data[64];
    memset(data, 0, 64);
    
    printf("Calling sha256_block_data_order via caller...\n");
    caller(state, data, 1);
    printf("Successfully returned.\n");
    
    return 0;
}
