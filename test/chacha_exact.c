// Exact mirror of CPython's chacha_init crash.
// Compile with: ./chibicc -O3 -S and check offsets.
#include "test.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

// mi_random_ctx_t: 136 bytes (aligned to 4)
typedef struct {
  uint32_t input[16];    // 64 bytes
  uint32_t output[16];   // 64 bytes
  int      output_available;
  int      padding;      // fill to 136
} ctx_t;

__attribute__((noinline))
static void chacha_init(ctx_t *ctx, const uint8_t key[32], uint64_t nonce) {
  // line 102: memset(ctx, 0, sizeof(*ctx))
  memset(ctx, 0, sizeof(*ctx));
  for (size_t i = 0; i < 4; i++) {
    ctx->input[i] = 0x61707865;
  }
  for (size_t i = 0; i < 8; i++) {
    ctx->input[i + 4] = ((uint32_t*)key)[i];
  }
  ctx->input[12] = 0;
  ctx->input[13] = 0;
  ctx->input[14] = (uint32_t)nonce;
  ctx->input[15] = (uint32_t)(nonce >> 32);
}

__attribute__((noinline))
static void random_init_ex(ctx_t *ctx, int use_weak) {
  uint8_t key[32];
  memset(key, 0xAB, sizeof(key));
  if (!use_weak) {
    // simulate the OS random call - for simplicity just keep key
  }
  chacha_init(ctx, key, (uintptr_t)ctx);
}

// Test main - check the output
int main(void) {
  ctx_t ctx;
  random_init_ex(&ctx, 0);
  
  // Check that input was properly initialized
  // If memset corrupted key instead of ctx, input[4+] will have wrong values
  if (ctx.input[0] != 0x61707865) return 1;
  for (int i = 0; i < 8; i++) {
    if (ctx.input[i + 4] != 0xABABABAB) return 2;
  }
  
  // Check nonce
  uint64_t expected_nonce = (uintptr_t)&ctx;
  if (ctx.input[14] != (uint32_t)expected_nonce) return 3;
  if (ctx.input[15] != (uint32_t)(expected_nonce >> 32)) return 4;
  
  return 0;
}
