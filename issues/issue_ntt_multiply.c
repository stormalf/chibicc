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
  libcrux_ml_kem_vector_portable_vector_type_PortableVector a, b;
  memset(&a, 0, sizeof(a));
  memset(&b, 0, sizeof(b));
  for (int i = 0; i < 16; i++) { a.elements[i] = (int16_t)(i*1003 - 8000); b.elements[i] = (int16_t)(i*777 - 4000); }
  int16_t z0 = libcrux_ml_kem_polynomial_ZETAS_TIMES_MONTGOMERY_R[64+0];
  int16_t z1 = libcrux_ml_kem_polynomial_ZETAS_TIMES_MONTGOMERY_R[64+1];
  int16_t z2 = libcrux_ml_kem_polynomial_ZETAS_TIMES_MONTGOMERY_R[64+2];
  int16_t z3 = libcrux_ml_kem_polynomial_ZETAS_TIMES_MONTGOMERY_R[64+3];
  libcrux_ml_kem_vector_portable_vector_type_PortableVector out =
      libcrux_ml_kem_vector_portable_ntt_multiply_0d(&a, &b, z0, z1, z2, z3);
  /* reference: compute via direct call using cc-expected? We just print to compare chibicc vs cc */
  printf("OUT:");
  for (int i = 0; i < 16; i++) printf("%d ", (int)out.elements[i]);
  printf("\n");
  return 0;
}
