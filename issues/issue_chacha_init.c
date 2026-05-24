// Test: faithful reproduction of CPython's chacha_init crash pattern
#include "test.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
  uint32_t input[16];
  uint32_t output[16];
  int      output_available;
} my_random_ctx_t;

__attribute__((noinline))
static void my_chacha_init(my_random_ctx_t *ctx, const uint8_t key[32], uint64_t nonce) {
  memset(ctx, 0, sizeof(*ctx));
  for (int i = 0; i < 4; i++) {
    ctx->input[i] = 0x61707865;
  }
  for (int i = 0; i < 8; i++) {
    ctx->input[i + 4] = ((uint32_t*)key)[i];
  }
  ctx->input[12] = 0;
  ctx->input[13] = 0;
  ctx->input[14] = (uint32_t)nonce;
  ctx->input[15] = (uint32_t)(nonce >> 32);
}

__attribute__((noinline))
static void my_random_init_ex(my_random_ctx_t *ctx, int use_weak) {
  uint8_t key[32];
  memset(key, 0x42, sizeof(key));
  ctx->output_available = 0;
  my_chacha_init(ctx, key, (uintptr_t)ctx);
}

__attribute__((constructor))
static void my_process_init(void) {
  my_random_ctx_t ctx;
  my_random_init_ex(&ctx, 0);
  // Verify the context was properly initialized
  if (ctx.input[0] != 0x61707865) {
    exit(1);
  }
  // If key was stored somewhere else, input[4..11] would be wrong
  for (int i = 0; i < 8; i++) {
    if (ctx.input[i + 4] != 0x42424242) {
      exit(2);
    }
  }
  // nonce
  uint64_t expected_nonce = (uintptr_t)&ctx;
  if (ctx.input[14] != (uint32_t)expected_nonce ||
      ctx.input[15] != (uint32_t)(expected_nonce >> 32)) {
    exit(3);
  }
}

int main(void) {
  // If constructor runs successfully, this runs too
  my_random_ctx_t ctx;
  uint8_t key[32];
  memset(key, 0xAB, sizeof(key));
  my_chacha_init(&ctx, key, 0xDEADBEEF);
  if (ctx.input[0] != 0x61707865) return 4;
  if (ctx.input[4] != 0xABABABAB) return 5;
  return 0;
}
