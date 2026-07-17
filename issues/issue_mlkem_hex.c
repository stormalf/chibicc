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
	uint8_t kp_seed[64];
	uint8_t enc_seed[32];
	for (int i = 0; i < 64; i++) kp_seed[i] = (uint8_t)(i*7+3);
	for (int i = 0; i < 32; i++) enc_seed[i] = (uint8_t)(i*13+1);
	struct libcrux_mlkem768_keypair keypair =
	    libcrux_ml_kem_mlkem768_portable_generate_key_pair(kp_seed);
	struct libcrux_mlkem768_enc_result enc =
	    libcrux_ml_kem_mlkem768_portable_encapsulate(&keypair.pk, enc_seed);
	/* print pk, ct, ss as hex so we can diff chibicc vs cc */
	printf("PK:");
	for (size_t i = 0; i < sizeof(keypair.pk.value); i++) printf("%02x", keypair.pk.value[i]);
	printf("\nCT:");
	for (size_t i = 0; i < sizeof(enc.fst.value); i++) printf("%02x", enc.fst.value[i]);
	printf("\nSS:");
	for (size_t i = 0; i < sizeof(enc.snd); i++) printf("%02x", enc.snd[i]);
	printf("\n");
	uint8_t dec[32];
	libcrux_ml_kem_mlkem768_portable_decapsulate(&keypair.sk, &enc.fst, dec);
	printf("DEC:");
	for (size_t i = 0; i < 32; i++) printf("%02x", dec[i]);
	printf("\n");
	return 0;
}
