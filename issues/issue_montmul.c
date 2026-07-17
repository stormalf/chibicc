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
  /* test montgomery_multiply_fe_by_fer */
  int fails = 0;
  for (int t = 0; t < 200000; t += 137) {
    int16_t fe = (int16_t)(t - 100000);
    int16_t fer = (int16_t)(t*7 - 50000);
    int16_t got = libcrux_ml_kem_vector_portable_arithmetic_montgomery_multiply_fe_by_fer(fe, fer);
    /* reference: montgomery_reduce(fe*fer) */
    int32_t prod = (int32_t)fe * (int32_t)fer;
    int16_t ref = libcrux_ml_kem_vector_portable_arithmetic_montgomery_reduce_element(prod);
    if (got != ref) {
      printf("MUL_FE_BY_FER fail fe=%d fer=%d got=%d ref=%d\n", fe, fer, got, ref);
      fails++; if (fails>10) return 1;
    }
  }
  /* test multiply_by_constant_0d */
  for (int trial = 0; trial < 50; trial++) {
    libcrux_ml_kem_vector_portable_vector_type_PortableVector v;
    for (int j = 0; j < 16; j++) v.elements[j] = (int16_t)(j*131 + trial*977 - 8000);
    int16_t c = (int16_t)(trial*199 - 1600);
    libcrux_ml_kem_vector_portable_vector_type_PortableVector out =
        libcrux_ml_kem_vector_portable_multiply_by_constant_0d(v, c);
    libcrux_ml_kem_vector_portable_vector_type_PortableVector ref =
        libcrux_ml_kem_vector_portable_arithmetic_multiply_by_constant(v, c);
    for (int j = 0; j < 16; j++)
      if (out.elements[j] != ref.elements[j]) {
        printf("MUL_BY_CONST fail trial=%d j=%d got=%d ref=%d\n", trial, j, (int)out.elements[j], (int)ref.elements[j]);
        fails++; if (fails>10) return 1;
      }
  }
  if (fails) { printf("FAILED %d\n", fails); return 1; }
  printf("OK montgomery_multiply_fe_by_fer and multiply_by_constant correct\n");
  return 0;
}
