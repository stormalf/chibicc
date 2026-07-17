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

int main(void) {
  /* SHAKE256("abc") known test vector (first 32 bytes) */
  uint8_t data[] = "abc";
  uint8_t out[32] = {0};
  Eurydice_slice data_slice = { .ptr = data, .len = sizeof(data) - 1 };
  Eurydice_slice out_slice = { .ptr = out, .len = 32 };
  libcrux_sha3_portable_shake256(out_slice, data_slice);
  /* known SHAKE256("abc") first 32 bytes */
  static const uint8_t ref[32] = {
    0x48,0x33,0x47,0x38,0x1a,0x08,0xcf,0x76,0xb2,0xb4,0x64,0x86,0x6b,0x62,0x31,0x49,
    0x83,0x59,0x2f,0x57,0x3e,0x1a,0x49,0xf2,0x2c,0x5c,0x5f,0xa7,0x49,0x42,0xaa,0x4c
  };
  if (memcmp(out, ref, 32) != 0) {
    printf("SHAK256(abc) MISMATCH\n");
    for (int i = 0; i < 32; i++) printf("%02x", out[i]);
    printf("\nref: ");
    for (int i = 0; i < 32; i++) printf("%02x", ref[i]);
    printf("\n");
    return 1;
  }
  printf("OK SHAKE256(abc) correct\n");
  return 0;
}
