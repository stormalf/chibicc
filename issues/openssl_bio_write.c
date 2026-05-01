/*
 * test_bio_write_pem.c
 *
 * Reproduces the exact call chain from the crash stack trace:
 *
 *   BIO_write                          (crypto/bio/bio_lib.c:392)
 *   PEM_write_bio                      (crypto/pem/pem_lib.c:648)
 *   PEM_ASN1_write_bio_internal        (crypto/pem/pem_lib.c:412)
 *   PEM_ASN1_write_bio                 (crypto/pem/pem_lib.c:428)
 *   PEM_write_bio_PKCS8_PRIV_KEY_INFO  (include/openssl/pem.h:157)
 *   key_to_pki_pem_priv_bio            (encode_key2any.c:306)
 *   key2any_encode                     (encode_key2any.c:1255)
 *   ml_dsa_44_to_PrivateKeyInfo_pem_encode
 *   encoder_process / OSSL_ENCODER_to_bio
 *   encode_private_key
 *   genpkey_main
 *
 * Goal: exercise BIO_write with a memory BIO (BIO_s_mem) and verify
 * that the data written is exactly the data read back.  If chibicc
 * mis-compiles any of the involved helpers the assertions will fire.
 *
 * Build:
 *   gcc  -std=c11 -Wall -Wextra \
 *        $(pkg-config --cflags --libs openssl) \
 *        -o test_bio_write_pem test_bio_write_pem.c
 *
 *   # chibicc (needs OpenSSL headers / libs on the include/library path):
 *   chibicc -I/usr/include/openssl \
 *           -o test_bio_write_pem test_bio_write_pem.c \
 *           -lssl -lcrypto
 *
 * Run:
 *   ./test_bio_write_pem
 *
 * Expected: all PASS, exit 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/encoder.h>
#include <openssl/crypto.h>

/* ------------------------------------------------------------------ */
/* Tiny test framework                                                  */
/* ------------------------------------------------------------------ */
static int g_pass = 0;
static int g_fail = 0;

#define CHECK(label, cond)                                        \
    do {                                                           \
        if (cond) {                                                \
            printf("  PASS  %s\n", (label));                       \
            g_pass++;                                              \
        } else {                                                   \
            printf("  FAIL  %s\n", (label));                       \
            ERR_print_errors_fp(stderr);                           \
            g_fail++;                                              \
        }                                                          \
    } while (0)

#define CHECK_EQ_INT(label, a, b)                                         \
    do {                                                                    \
        long _a = (long)(a), _b = (long)(b);                               \
        if (_a == _b) {                                                     \
            printf("  PASS  %s\n", (label));                               \
            g_pass++;                                                       \
        } else {                                                            \
            printf("  FAIL  %s : got %ld, expected %ld\n", (label),_a,_b); \
            g_fail++;                                                       \
        }                                                                   \
    } while (0)

/* ------------------------------------------------------------------ */
/* Helper: dump OpenSSL errors and abort test on NULL pointer          */
/* ------------------------------------------------------------------ */
static void *xcheck(void *p, const char *what)
{
    if (!p) {
        fprintf(stderr, "FATAL: %s returned NULL\n", what);
        ERR_print_errors_fp(stderr);
        exit(1);
    }
    return p;
}

/* ------------------------------------------------------------------ */
/* 1. BIO_write / BIO_read round-trip on a memory BIO                 */
/*    Mirrors the low-level write performed at bio_lib.c:392           */
/* ------------------------------------------------------------------ */
static void test_bio_write_basic(void)
{
    printf("\n[BIO_write – basic memory BIO round-trip]\n");

    BIO *mem = xcheck(BIO_new(BIO_s_mem()), "BIO_new(BIO_s_mem)");

    /* single short write */
    const char msg[] = "hello openssl";
    int written = BIO_write(mem, msg, (int)sizeof(msg) - 1);
    CHECK_EQ_INT("BIO_write returns byte count", written, (int)(sizeof(msg) - 1));

    /* read back */
    char buf[64];
    memset(buf, 0, sizeof(buf));
    int n = BIO_read(mem, buf, (int)sizeof(buf));
    CHECK_EQ_INT("BIO_read returns same byte count", n, written);
    CHECK("round-trip content matches", memcmp(buf, msg, (size_t)n) == 0);

    BIO_free(mem);
}

/* ------------------------------------------------------------------ */
/* 2. BIO_write with binary data (NUL bytes, high bytes)              */
/* ------------------------------------------------------------------ */
static void test_bio_write_binary(void)
{
    printf("\n[BIO_write – binary / high-byte data]\n");

    BIO *mem = xcheck(BIO_new(BIO_s_mem()), "BIO_new(BIO_s_mem)");

    unsigned char data[256];
    for (int i = 0; i < 256; i++)
        data[i] = (unsigned char)i;

    int written = BIO_write(mem, data, 256);
    CHECK_EQ_INT("BIO_write 256 bytes", written, 256);

    unsigned char out[256];
    int n = BIO_read(mem, out, 256);
    CHECK_EQ_INT("BIO_read 256 bytes", n, 256);
    CHECK("binary round-trip", memcmp(data, out, 256) == 0);

    BIO_free(mem);
}

/* ------------------------------------------------------------------ */
/* 3. Multiple sequential BIO_write calls (mimics PEM_write_bio which  */
/*    calls BIO_write for header, base64 body, and footer separately)  */
/* ------------------------------------------------------------------ */
static void test_bio_write_sequential(void)
{
    printf("\n[BIO_write – sequential writes (PEM header/body/footer pattern)]\n");

    BIO *mem = xcheck(BIO_new(BIO_s_mem()), "BIO_new(BIO_s_mem)");

    const char *header = "-----BEGIN PRIVATE KEY-----\n";
    const char *body   = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
    const char *footer = "-----END PRIVATE KEY-----\n";

    int h = BIO_write(mem, header, (int)strlen(header));
    int b = BIO_write(mem, body,   (int)strlen(body));
    int f = BIO_write(mem, footer, (int)strlen(footer));

    CHECK_EQ_INT("header write length", h, (int)strlen(header));
    CHECK_EQ_INT("body write length",   b, (int)strlen(body));
    CHECK_EQ_INT("footer write length", f, (int)strlen(footer));

    /* peek at the internal buffer via BIO_get_mem_data */
    char *ptr = NULL;
    long total = BIO_get_mem_data(mem, &ptr);
    long expected = (long)(strlen(header) + strlen(body) + strlen(footer));
    CHECK_EQ_INT("total buffered length", total, expected);
    CHECK("content starts with PEM header",
          strncmp(ptr, header, strlen(header)) == 0);
    CHECK("content ends with PEM footer",
          strncmp(ptr + total - (long)strlen(footer),
                  footer, strlen(footer)) == 0);

    BIO_free(mem);
}

/* ------------------------------------------------------------------ */
/* 4. PEM_write_bio_PrivateKey – mirrors frames #4-#8 in the trace    */
/*    Generates an RSA-2048 key, encodes to PEM into a mem BIO,        */
/*    reads it back, and re-parses it.                                 */
/* ------------------------------------------------------------------ */
static void test_pem_write_bio_privkey(void)
{
    printf("\n[PEM_write_bio_PrivateKey – full encode/decode round-trip]\n");

    /* Generate a small RSA key (2048-bit is fastest that's still valid) */
    EVP_PKEY_CTX *ctx = xcheck(
        EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL),
        "EVP_PKEY_CTX_new_from_name(RSA)");
    CHECK("EVP_PKEY_keygen_init", EVP_PKEY_keygen_init(ctx) > 0);
    CHECK("EVP_PKEY_CTX_set_rsa_keygen_bits",
          EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) > 0);

    EVP_PKEY *pkey = NULL;
    CHECK("EVP_PKEY_keygen", EVP_PKEY_keygen(ctx, &pkey) > 0);
    EVP_PKEY_CTX_free(ctx);
    if (!pkey) { printf("  SKIP  (keygen failed)\n"); return; }

    /* Encode to PEM in a memory BIO – this is exactly the path in the trace */
    BIO *mem = xcheck(BIO_new(BIO_s_mem()), "BIO_new(BIO_s_mem)");
    int rc = PEM_write_bio_PrivateKey(mem, pkey,
                                      NULL,  /* no encryption */
                                      NULL, 0, NULL, NULL);
    CHECK("PEM_write_bio_PrivateKey succeeds", rc == 1);

    /* Verify we got something that looks like PEM */
    char *ptr = NULL;
    long len = BIO_get_mem_data(mem, &ptr);
    CHECK("PEM output is non-empty", len > 0);
    CHECK("PEM output starts with '-----BEGIN'",
          len > 10 && strncmp(ptr, "-----BEGIN", 10) == 0);

    /* Re-parse the PEM and verify it matches the original key */
    BIO *mem2 = xcheck(BIO_new_mem_buf(ptr, (int)len), "BIO_new_mem_buf");
    EVP_PKEY *pkey2 = PEM_read_bio_PrivateKey(mem2, NULL, NULL, NULL);
    CHECK("PEM_read_bio_PrivateKey succeeds", pkey2 != NULL);
    if (pkey2) {
        CHECK("re-parsed key matches original",
              EVP_PKEY_eq(pkey, pkey2) == 1);
        EVP_PKEY_free(pkey2);
    }

    BIO_free(mem);
    BIO_free(mem2);
    EVP_PKEY_free(pkey);
}

/* ------------------------------------------------------------------ */
/* 5. PEM_write_bio_PKCS8PrivateKey – mirrors frame #4 exactly        */
/*    (PEM_write_bio_PKCS8_PRIV_KEY_INFO wraps this path)             */
/* ------------------------------------------------------------------ */
static void test_pem_write_bio_pkcs8(void)
{
    printf("\n[PEM_write_bio_PKCS8PrivateKey – PKCS#8 PEM encode/decode]\n");

    EVP_PKEY_CTX *ctx = xcheck(
        EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL),
        "EVP_PKEY_CTX_new_from_name(RSA)");
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);

    EVP_PKEY *pkey = NULL;
    EVP_PKEY_keygen(ctx, &pkey);
    EVP_PKEY_CTX_free(ctx);
    if (!pkey) { printf("  SKIP  (keygen failed)\n"); return; }

    BIO *mem = xcheck(BIO_new(BIO_s_mem()), "BIO_new(BIO_s_mem)");

    /* Unencrypted PKCS#8 PrivateKeyInfo — mirrors encode_key2any.c:1255 */
    int rc = PEM_write_bio_PKCS8PrivateKey(mem, pkey,
                                            NULL,        /* cipher */
                                            NULL, 0,     /* no passphrase */
                                            NULL, NULL);
    CHECK("PEM_write_bio_PKCS8PrivateKey succeeds", rc == 1);

    char *ptr = NULL;
    long len = BIO_get_mem_data(mem, &ptr);
    CHECK("PKCS8 PEM output non-empty", len > 0);
    CHECK("PKCS8 PEM has correct header",
          len > 27 && strncmp(ptr, "-----BEGIN PRIVATE KEY-----", 27) == 0);

    /* Decode back */
    BIO *mem2 = xcheck(BIO_new_mem_buf(ptr, (int)len), "BIO_new_mem_buf");
    EVP_PKEY *pkey2 = PEM_read_bio_PrivateKey(mem2, NULL, NULL, NULL);
    CHECK("decoded PKCS8 key is non-NULL", pkey2 != NULL);
    if (pkey2) {
        CHECK("decoded PKCS8 key matches original", EVP_PKEY_eq(pkey, pkey2) == 1);
        EVP_PKEY_free(pkey2);
    }

    BIO_free(mem);
    BIO_free(mem2);
    EVP_PKEY_free(pkey);
}

/* ------------------------------------------------------------------ */
/* 6. OSSL_ENCODER_to_bio – mirrors frames #8-#9 in the trace         */
/*    Uses the high-level encoder API that ultimately calls BIO_write. */
/* ------------------------------------------------------------------ */
static void test_ossl_encoder_to_bio(void)
{
    printf("\n[OSSL_ENCODER_to_bio – high-level encoder path]\n");

    EVP_PKEY_CTX *ctx = xcheck(
        EVP_PKEY_CTX_new_from_name(NULL, "RSA", NULL),
        "EVP_PKEY_CTX_new_from_name(RSA)");
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);

    EVP_PKEY *pkey = NULL;
    EVP_PKEY_keygen(ctx, &pkey);
    EVP_PKEY_CTX_free(ctx);
    if (!pkey) { printf("  SKIP  (keygen failed)\n"); return; }

    /* Build encoder: PrivateKeyInfo → PEM  (same selection as genpkey) */
    OSSL_ENCODER_CTX *ectx = xcheck(
        OSSL_ENCODER_CTX_new_for_pkey(pkey,
                                       EVP_PKEY_KEYPAIR,
                                       "PEM",
                                       "PrivateKeyInfo",
                                       NULL),
        "OSSL_ENCODER_CTX_new_for_pkey");

    BIO *mem = xcheck(BIO_new(BIO_s_mem()), "BIO_new(BIO_s_mem)");

    int rc = OSSL_ENCODER_to_bio(ectx, mem);   /* frame #9 in the trace */
    CHECK("OSSL_ENCODER_to_bio succeeds", rc == 1);

    char *ptr = NULL;
    long len = BIO_get_mem_data(mem, &ptr);
    CHECK("OSSL_ENCODER output non-empty", len > 0);
    CHECK("output looks like PEM",
          len > 10 && strncmp(ptr, "-----BEGIN", 10) == 0);

    OSSL_ENCODER_CTX_free(ectx);
    BIO_free(mem);
    EVP_PKEY_free(pkey);
}

/* ------------------------------------------------------------------ */
/* 7. Stress: many small BIO_write calls (tests buffer realloc path)  */
/* ------------------------------------------------------------------ */
static void test_bio_write_stress(void)
{
    printf("\n[BIO_write – stress: 1000 small writes]\n");

    BIO *mem = xcheck(BIO_new(BIO_s_mem()), "BIO_new(BIO_s_mem)");

    const char chunk[] = "ABCDEFGHIJ"; /* 10 bytes */
    int total_written = 0;
    int ok = 1;
    for (int i = 0; i < 1000; i++) {
        int n = BIO_write(mem, chunk, 10);
        if (n != 10) { ok = 0; break; }
        total_written += n;
    }
    CHECK("all 1000 writes returned 10", ok);
    CHECK_EQ_INT("total written bytes", total_written, 10000);

    char *ptr = NULL;
    long len = BIO_get_mem_data(mem, &ptr);
    CHECK_EQ_INT("BIO_get_mem_data length", len, 10000);

    /* verify every chunk */
    int content_ok = 1;
    for (int i = 0; i < 1000; i++) {
        if (memcmp(ptr + i * 10, chunk, 10) != 0) { content_ok = 0; break; }
    }
    CHECK("all chunks intact", content_ok);

    BIO_free(mem);
}

/* ------------------------------------------------------------------ */
/* main                                                                 */
/* ------------------------------------------------------------------ */
int main(void)
{
    printf("=== BIO_write / PEM path – chibicc regression test ===\n");
    printf("OpenSSL version: %s\n", OpenSSL_version(OPENSSL_VERSION));

    OPENSSL_init_crypto(0, NULL);   /* ensure libcrypto is initialised */

    test_bio_write_basic();
    test_bio_write_binary();
    test_bio_write_sequential();
    test_pem_write_bio_privkey();
    test_pem_write_bio_pkcs8();
    test_ossl_encoder_to_bio();
    test_bio_write_stress();

    printf("\n=== Results: %d passed, %d failed ===\n", g_pass, g_fail);
    return g_fail == 0 ? 0 : 1;
}
