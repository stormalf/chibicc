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
  int16_t coeffs[256];
  for (int i = 0; i < 256; i++) coeffs[i] = (int16_t)(i*131 + 777 - 16000);
  libcrux_ml_kem_polynomial_PolynomialRingElement_f0 p =
      libcrux_ml_kem_polynomial_from_i16_array_89_c1(
          Eurydice_array_to_slice((size_t)256U, coeffs, int16_t));
  libcrux_ml_kem_ntt_ntt_binomially_sampled_ring_element_0f(&p);
  /* print all 256 coefficients so we can diff chibicc vs cc */
  for (int i = 0; i < 256; i++)
    printf("%d\n", (int)p.coefficients[i/16].elements[i%16]);
  return 0;
}
