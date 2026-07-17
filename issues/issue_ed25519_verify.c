/* Standalone ed25519 sign/verify repro for chibicc LLVM backend bug. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <openssl/evp.h>

typedef int8_t crypto_int8;
typedef uint8_t crypto_uint8;
typedef int16_t crypto_int16;
typedef uint16_t crypto_uint16;
typedef int32_t crypto_int32;
typedef uint32_t crypto_uint32;
typedef int64_t crypto_int64;
typedef uint64_t crypto_uint64;

#define crypto_hash_sha512_BYTES 64U
#define crypto_sign_ed25519_SECRETKEYBYTES 64U
#define crypto_sign_ed25519_PUBLICKEYBYTES 32U
#define crypto_sign_ed25519_BYTES 64U

int crypto_hash_sha512(unsigned char *out, const unsigned char *in,
    unsigned long long inlen) {
  if (!EVP_Digest(in, inlen, out, NULL, EVP_sha512(), NULL))
    return -1;
  return 0;
}

void arc4random_buf(void *buf, size_t n) {
  static unsigned seed = 1;
  unsigned char *p = buf;
  for (size_t i = 0; i < n; i++) p[i] = (unsigned char)(rand_r(&seed) & 0xff);
}
unsigned int arc4random(void) { return (unsigned)rand(); }

#define randombytes(buf, len) arc4random_buf((buf), (len))
#define small_random32() arc4random()

/* Pull in the real openssh ed25519 implementation. */
#include "/home/stormalf/openssh-portable/ed25519.c"

int main(void) {
  unsigned char sk[64], pk[32];
  if (crypto_sign_ed25519_keypair(pk, sk) != 0) {
    fprintf(stderr, "keypair failed\n");
    return 2;
  }
  const char *msg = "hello ed25519 chibicc repro";
  unsigned long long mlen = strlen(msg);
  unsigned char sm[256];
  unsigned long long smlen = 0;
  if (crypto_sign_ed25519(sm, &smlen, (const unsigned char *)msg, mlen, sk) != 0) {
    fprintf(stderr, "sign failed\n");
    return 3;
  }
  unsigned char mout[256];
  unsigned long long moutlen = 0;
  int rc = crypto_sign_ed25519_open(mout, &moutlen, sm, smlen, pk);
  if (rc != 0) {
    fprintf(stderr, "VERIFY FAILED rc=%d\n", rc);
    return 1;
  }
  if (moutlen != mlen || memcmp(mout, msg, mlen) != 0) {
    fprintf(stderr, "VERIFY MISMATCH\n");
    return 4;
  }
  /* negative test: tamper signature */
  unsigned char sm2[256];
  memcpy(sm2, sm, smlen);
  sm2[0] ^= 0xff;
  rc = crypto_sign_ed25519_open(mout, &moutlen, sm2, smlen, pk);
  if (rc == 0) {
    fprintf(stderr, "TAMPER ACCEPTED (should fail)\n");
    return 5;
  }
  printf("OK ed25519 sign/verify works\n");
  return 0;
}
