#include "config.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <err.h>
#include "crypto_api.h"
#define fatal_f(x) exit(1)
#include "libcrux_mlkem768_sha3.h"

static int cmphex(const char *name, const uint8_t *a, const uint8_t *b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (a[i] != b[i]) {
      printf("%s MISMATCH at %zu: %02x vs %02x\n", name, i, a[i], b[i]);
      return 1;
    }
  }
  printf("%s match (%zu bytes)\n", name, n);
  return 0;
}

int main(void) {
	struct libcrux_mlkem768_keypair keypair = {0};
	uint8_t kp_seed[64] = {0}, enc_seed[32] = {0};

	keypair = libcrux_ml_kem_mlkem768_portable_generate_key_pair(kp_seed);
	int valid = libcrux_ml_kem_mlkem768_portable_validate_public_key(&keypair.pk);
	printf("validate_public_key=%d\n", valid);
	if (!valid) errx(1, "valid smoke failed");

	/* encapsulate twice with same seed -> deterministic? */
	struct libcrux_mlkem768_enc_result e1 =
	    libcrux_ml_kem_mlkem768_portable_encapsulate(&keypair.pk, enc_seed);
	struct libcrux_mlkem768_enc_result e2 =
	    libcrux_ml_kem_mlkem768_portable_encapsulate(&keypair.pk, enc_seed);
	cmphex("enc deterministic ct", e1.fst.value, e2.fst.value, sizeof(e1.fst.value));
	cmphex("enc deterministic ss", e1.snd, e2.snd, sizeof(e1.snd));

	uint8_t dec[32];
	libcrux_ml_kem_mlkem768_portable_decapsulate(&keypair.sk, &e1.fst, dec);
	cmphex("enc.ss vs decap.ss", e1.snd, dec, sizeof(dec));

	/* decapsulate should be deterministic regardless of ss output var */
	uint8_t dec2[32];
	libcrux_ml_kem_mlkem768_portable_decapsulate(&keypair.sk, &e1.fst, dec2);
	cmphex("decap deterministic", dec, dec2, sizeof(dec));
	return 0;
}
