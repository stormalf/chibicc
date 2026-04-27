#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint32_t OPENSSL_ia32cap_P[4] = {0, 0, 0, 0};

void sha512_block_data_order(uint64_t *state, const void *data, size_t num_blocks);

void __attribute__((noinline)) caller(uint64_t *state, const void *data, size_t num_blocks) {
    char padding[1];
    padding[0] = 0;
    sha512_block_data_order(state, data, num_blocks);
    (void)padding;
}

int main() {
    uint64_t state[8] = {
        0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
        0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
    };
    unsigned char data[128];
    memset(data, 0, 128);
    
    printf("Calling sha512_block_data_order via caller...\n");
    caller(state, data, 1);
    printf("Successfully returned.\n");
    
    return 0;
}
