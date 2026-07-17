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

static int ref_get_n_lsb(uint32_t x, uint8_t n) {
  return (int)(x & ((1U << n) - 1U));
}

int main(void) {
  int fails = 0;
  /* test get_n_least_significant_bits */
  for (uint32_t x = 0; x < 70000; x += 37) {
    for (uint8_t b = 0; b <= 16; b++) {
      uint32_t a = libcrux_ml_kem_vector_portable_arithmetic_get_n_least_significant_bits((uint8_t)b, x);
      uint32_t r = ref_get_n_lsb(x, b);
      if (a != r) {
        printf("GET_N_LSB fail x=%u b=%u got=%u ref=%u\n", x, b, a, r);
        fails++; if (fails>8) return 1;
      }
    }
  }
  /* test cond_subtract_3329 on a vector */
  libcrux_ml_kem_vector_portable_vector_type_PortableVector v;
  for (int j = 0; j < 16; j++) v.elements[j] = (int16_t)(j*1000 - 5000);
  libcrux_ml_kem_vector_portable_vector_type_PortableVector out =
      libcrux_ml_kem_vector_portable_arithmetic_cond_subtract_3329(v);
  for (int j = 0; j < 16; j++) {
    int16_t expected = (out.elements[j] >= 3329) ? (int16_t)(out.elements[j]-3329) : out.elements[j];
    /* reference: v - 3329 if v >= 3329+1664 i.e. >= 4993? Actually cond_subtract subtracts 3329 when v >= 3329 means... just check it equals reference formula */
    int16_t ref = (v.elements[j] >= 3329) ? (int16_t)(v.elements[j] - 3329) : v.elements[j];
    if (out.elements[j] != ref) {
      printf("COND_SUB fail j=%d v=%d got=%d ref=%d\n", j, (int)v.elements[j], (int)out.elements[j], (int)ref);
      fails++; if (fails>8) return 1;
    }
    (void)expected;
  }
  /* test bitwise_and_with_constant */
  for (int i = 0; i < 100; i++) {
    libcrux_ml_kem_vector_portable_vector_type_PortableVector a;
    for (int j = 0; j < 16; j++) a.elements[j] = (int16_t)(i*131+j*7-4000);
    libcrux_ml_kem_vector_portable_vector_type_PortableVector r =
        libcrux_ml_kem_vector_portable_arithmetic_bitwise_and_with_constant(a, (int16_t)0x0f0f);
    for (int j = 0; j < 16; j++)
      if (r.elements[j] != (int16_t)(a.elements[j] & 0x0f0f)) { printf("AND fail\n"); fails++; }
    if (fails>8) return 1;
  }
  /* test add and sub vectors */
  for (int i = 0; i < 100; i++) {
    libcrux_ml_kem_vector_portable_vector_type_PortableVector a, b;
    for (int j = 0; j < 16; j++) { a.elements[j]=(int16_t)(i*131+j*7-4000); b.elements[j]=(int16_t)(j*311-i*13+2000); }
    libcrux_ml_kem_vector_portable_vector_type_PortableVector sa = libcrux_ml_kem_vector_portable_arithmetic_sub(b, a);
    libcrux_ml_kem_vector_portable_vector_type_PortableVector ad = libcrux_ml_kem_vector_portable_arithmetic_add(a, b);
    for (int j = 0; j < 16; j++) {
      if (sa.elements[j] != (int16_t)(b.elements[j] - a.elements[j])) { printf("SUB fail\n"); fails++; }
      if (ad.elements[j] != (int16_t)(a.elements[j] + b.elements[j])) { printf("ADD fail\n"); fails++; }
    }
    if (fails>8) return 1;
  }
  if (fails) { printf("FAILED %d\n", fails); return 1; }
  printf("OK leaf arithmetic correct\n");
  return 0;
}
