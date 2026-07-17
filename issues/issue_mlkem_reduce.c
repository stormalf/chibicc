#include "config.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include "crypto_api.h"
#define fatal_f(x) exit(1)
#include "libcrux_mlkem768_sha3.h"

/* reference implementations matching the C semantics above */
static int16_t ref_mont(int32_t value) {
  int32_t k = (int32_t)(int16_t)value * (int32_t)62209U;
  int32_t kt = (int32_t)(int16_t)k * (int32_t)3329;
  int16_t c = (int16_t)(kt >> 16U);
  int16_t vh = (int16_t)(value >> 16U);
  return vh - c;
}
static int16_t ref_barrett(int16_t value) {
  int32_t t = (int32_t)value * 20159 + (1U << 25);
  int16_t q = (int16_t)(t >> 26U);
  return value - q * 3329;
}

int main(void) {
  int fails = 0;
  for (int32_t v = -2000000000; v <= 2000000000; v += 123457) {
    int16_t a = libcrux_ml_kem_vector_portable_arithmetic_montgomery_reduce_element(v);
    int16_t b = ref_mont(v);
    if (a != b) { printf("MONT mismatch v=%d got=%d ref=%d\n", v, a, b); fails++; if (fails>5) break; }
  }
  /* barrett takes int16 */
  for (int i = -32768; i <= 32767; i++) {
    int16_t x = (int16_t)i;
    int16_t a = libcrux_ml_kem_vector_portable_arithmetic_barrett_reduce_element(x);
    int16_t b = ref_barrett(x);
    if (a != b) { printf("BARRETT mismatch x=%d got=%d ref=%d\n", x, a, b); fails++; if (fails>5) break; }
  }
  if (fails) { printf("FAILED %d\n", fails); return 1; }
  printf("OK montgomery/barrett reduce correct\n");
  return 0;
}
