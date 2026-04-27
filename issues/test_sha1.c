#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t OPENSSL_ia32cap_P[4] = {0, 0, 0, 0};

void sha1_block_data_order(uint32_t *state, const void *data, size_t num_blocks);

void __attribute__((noinline)) caller(uint32_t *state, const void *data, size_t num_blocks) {
    char padding[1];
    padding[0] = 0;
    sha1_block_data_order(state, data, num_blocks);
    (void)padding;
}

int main() {
    uint32_t state[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    unsigned char data[64];
    memset(data, 0, 64);
    
    printf("Calling sha1_block_data_order via caller...\n");
    caller(state, data, 1);
    printf("Successfully returned.\n");
    
    return 0;
}
