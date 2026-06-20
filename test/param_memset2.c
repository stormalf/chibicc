// Test: faithful reproduction of chacha_init's memset pattern
// chibicc -O3 may access the wrong parameter offset after pushes
#include "test.h"
#include <string.h>
#include <stdint.h>

typedef struct {
    uint64_t data[12];  // 96 bytes like chacha_ctx
    int flag;
} MyCtx;

__attribute__((noinline))
static void test_func(MyCtx *ctx, const unsigned char key[32], unsigned long long nonce) {
    // Just like chacha_init: memset(ctx, 0, sizeof(*ctx))
    // Then use key and nonce to prevent dead code elimination
    memset(ctx, 0, sizeof(*ctx));
    ctx->flag = 42;
    ctx->data[0] = nonce;
    ctx->data[1] = key[0];
    ctx->data[2] = key[31];
}

int main(void) {
    MyCtx ctx;
    unsigned char key[32];
    memset(key, 0xAB, sizeof(key));
    ctx.flag = 0;

    test_func(&ctx, key, 0xDEADBEEF);

    if (ctx.flag != 42) return 1;
    if (ctx.data[0] != 0xDEADBEEF) return 2;
    if (ctx.data[1] != 0xAB) return 3;
    if (ctx.data[2] != 0xAB) return 4;
    return 0;
}
