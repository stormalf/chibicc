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
  int fails = 0;
  /* Build a polynomial from known coefficients, apply forward NTT, compare. */
  for (int trial = 0; trial < 50; trial++) {
    int16_t coeffs[256];
    for (int i = 0; i < 256; i++) coeffs[i] = (int16_t)(i*131 + trial*977 - 16000);
    libcrux_ml_kem_polynomial_PolynomialRingElement_f0 p =
        libcrux_ml_kem_polynomial_from_i16_array_89_c1(
            Eurydice_array_to_slice((size_t)256U, coeffs, int16_t));
    libcrux_ml_kem_ntt_ntt_binomially_sampled_ring_element_0f(&p);
    /* reference computed by cc in a second run; instead re-derive via inverse check:
       applying invert_ntt should give back original (mod 3329) */
    libcrux_ml_kem_polynomial_PolynomialRingElement_f0 q = p;
    libcrux_ml_kem_invert_ntt_invert_ntt_montgomery_f6(&q);
    /* q should equal original coeffs reduced mod 3329 */
    for (int i = 0; i < 256; i++) {
      int expected = ((int)coeffs[i] % 3329 + 3329) % 3329;
      if (expected > 1664) expected -= 3329;
      if (q.coefficients[i/16].elements[i%16] != (int16_t)expected) {
        printf("NTT roundtrip fail trial=%d i=%d got=%d expected=%d\n",
               trial, i, (int)q.coefficients[i/16].elements[i%16], expected);
        fails++; if (fails>10) return 1;
      }
    }
  }
  if (fails) { printf("FAILED %d\n", fails); return 1; }
  printf("OK NTT/invert_NTT roundtrip correct\n");
  return 0;
}
