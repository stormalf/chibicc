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
int main(void) {
	struct libcrux_mlkem768_keypair keypair = {0};
	struct libcrux_mlkem768_pk pk = {0};
	struct libcrux_mlkem768_sk sk = {0};
	struct libcrux_mlkem768_ciphertext ct = {0};
	struct libcrux_mlkem768_enc_result enc_result = {0};
	uint8_t kp_seed[64] = {0}, enc_seed[32] = {0};
	uint8_t shared_key[crypto_kem_mlkem768_BYTES];

	if (sizeof(keypair.pk.value) != crypto_kem_mlkem768_PUBLICKEYBYTES)
		errx(1, "keypair.pk bad");
	if (sizeof(keypair.sk.value) != crypto_kem_mlkem768_SECRETKEYBYTES)
		errx(1, "keypair.sk bad");
	if (sizeof(pk.value) != crypto_kem_mlkem768_PUBLICKEYBYTES)
		errx(1, "pk bad");
	if (sizeof(sk.value) != crypto_kem_mlkem768_SECRETKEYBYTES)
		errx(1, "sk bad");
	if (sizeof(ct.value) != crypto_kem_mlkem768_CIPHERTEXTBYTES)
		errx(1, "ct bad");
	if (sizeof(enc_result.fst.value) != crypto_kem_mlkem768_CIPHERTEXTBYTES)
		errx(1, "enc_result ct bad");
	if (sizeof(enc_result.snd) != crypto_kem_mlkem768_BYTES)
		errx(1, "enc_result shared key bad");

	keypair = libcrux_ml_kem_mlkem768_portable_generate_key_pair(kp_seed);
	if (!libcrux_ml_kem_mlkem768_portable_validate_public_key(&keypair.pk))
		errx(1, "valid smoke failed");
	enc_result = libcrux_ml_kem_mlkem768_portable_encapsulate(&keypair.pk,
	    enc_seed);
	libcrux_ml_kem_mlkem768_portable_decapsulate(&keypair.sk,
	    &enc_result.fst, shared_key);
	if (memcmp(shared_key, enc_result.snd, sizeof(shared_key)) != 0)
		errx(1, "smoke failed");
	printf("OK mlkem768 roundtrip works\n");
	return 0;
}
