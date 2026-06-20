// Test: function with pointer + array parameters, calling memset(param1, ...)
// chibicc -O3 may access the wrong parameter when depth > 0
#include "test.h"
#include <string.h>

typedef struct {
    unsigned long long data[4];
    int flag;
} MyCtx;

static void my_func(MyCtx *ctx, const unsigned char key[32], unsigned long long nonce) {
    // This memset should use ctx, but chibicc -O3 may use key instead
    memset(ctx, 0, sizeof(*ctx));
    
    // If memset corrupted the wrong memory, this check catches it
    if (ctx->flag != 0) {
        exit(1);
    }
    
    // Verify key is still intact (nonce prevents tail call)
    if (key[0] != 0xAB || key[31] != 0xCD) {
        exit(2);
    }
    
    ctx->flag = 42;
    ctx->data[0] = nonce;
}

int main(void) {
    MyCtx ctx;
    unsigned char key[32];
    
    // Initialize key
    memset(key, 0, sizeof(key));
    key[0] = 0xAB;
    key[31] = 0xCD;
    
    ctx.flag = 0;
    
    my_func(&ctx, key, 0xDEADBEEF);
    
    if (ctx.flag != 42) {
        return 3;
    }
    if (ctx.data[0] != 0xDEADBEEF) {
        return 4;
    }
    
    return 0;
}
