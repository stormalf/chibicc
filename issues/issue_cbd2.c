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

/* reference CBD eta=2 */
static int16_t ref_cbd2(uint32_t t, int idx) {
  uint32_t even = t & 0x55555555U;
  uint32_t odd  = (t >> 1) & 0x55555555U;
  uint32_t c = even + odd;
  int o1 = (c >> (idx*4)) & 3U;
  int o2 = (c >> (idx*4+2)) & 3U;
  return (int16_t)(o1 - o2);
}

int main(void) {
  int fails = 0;
  for (uint32_t t = 0; t < 0x1000000; t += 99991) {
    uint8_t bytes[4] = { (uint8_t)t, (uint8_t)(t>>8), (uint8_t)(t>>16), (uint8_t)(t>>24) };
    Eurydice_slice s = { .ptr = bytes, .len = 4 };
    libcrux_ml_kem_polynomial_PolynomialRingElement_f0 r =
        libcrux_ml_kem_sampling_sample_from_binomial_distribution_2_85(s);
    for (int i = 0; i < 8; i++) {
      int16_t got = r.coefficients[0].elements[i];
      int16_t ref = ref_cbd2(t, i);
      if (got != ref) {
        printf("CBD2 fail t=%u i=%d got=%d ref=%d\n", t, i, (int)got, (int)ref);
        fails++; if (fails>10) return 1;
      }
    }
  }
  if (fails) { printf("FAILED %d\n", fails); return 1; }
  printf("OK CBD eta=2 sampling correct\n");
  return 0;
}
