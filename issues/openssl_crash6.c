// test_poly1305_abi.c
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// Assembly functions
void poly1305_init(void *ctx, const unsigned char key[32]);
void poly1305_blocks(void *ctx, const unsigned char *m, size_t len, uint32_t padbit);
void poly1305_emit(void *ctx, unsigned char mac[16], const unsigned int nonce[4]);

// Poly1305 context size (from OpenSSL)
typedef struct {
    uint64_t r[3];
    uint64_t h[3];
    uint64_t pad[2];
} poly1305_ctx;

int main() {
    // RFC 8439 test vector
    const unsigned char key[32] = {
        0x85,0xd6,0xbe,0x78,0x57,0x55,0x6d,0x33,
        0x7f,0x44,0x52,0xfe,0x42,0xd5,0x06,0xa8,
        0x01,0x03,0x80,0x8a,0xfb,0x0d,0xf1,0xce,
        0x10,0x6c,0x6a,0x10,0x16,0x3b,0xa7,0x4d
    };

    const unsigned char msg[] = "Cryptographic Forum Research Group";

    const unsigned char expected[16] = {
        0xa8,0x06,0x1d,0xc1,0x30,0x51,0x36,0xc6,
        0xc2,0x2b,0x8b,0xaf,0x0c,0x01,0x27,0xa9
    };

    poly1305_ctx ctx;
    unsigned char mac[16];

    memset(&ctx, 0, sizeof(ctx));

    // --- Call assembly ---
    poly1305_init(&ctx, key);
    poly1305_blocks(&ctx, msg, sizeof(msg) - 1, 1);
    poly1305_emit(&ctx, mac, (const unsigned int *)(key + 16));

    // --- Verify ---
    if (memcmp(mac, expected, 16) != 0) {
        printf("got:      ");
        for (int i = 0; i < 16; i++) printf("%02x", mac[i]);
        printf("\nexpected: ");
        for (int i = 0; i < 16; i++) printf("%02x", expected[i]);
        printf("\n");
        return 0;
    }

    printf("OK\n");
    return 0;
}
