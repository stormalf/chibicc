/*
 * repro_test_sslapi.c
 *
 * Minimal reproduction for OpenSSL test_sslapi failures when compiled with chibicc.
 * This test exercises SSL context initialization and basic object lifecycle, 
 * which are often the first points of failure due to stack alignment issues 
 * or incorrect structure padding/alignment in the SSL state machine.
 */

#include <stdio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>

static void dump_errors(void) {
    ERR_print_errors_fp(stderr);
}

int main(void) {
    SSL_CTX *ctx = NULL;
    SSL *ssl = NULL;
    const SSL_METHOD *method = NULL;
    BIO *rbio = NULL, *wbio = NULL;

    printf("Starting SSL API reproduction test...\n");

    /* Initialize the SSL library */
    OPENSSL_init_ssl(OPENSSL_INIT_LOAD_SSL_STRINGS | OPENSSL_INIT_LOAD_CRYPTO_STRINGS, NULL);

    method = TLS_method();
    if (method == NULL) {
        fprintf(stderr, "Error: TLS_method() returned NULL\n");
        return 1;
    }

    ctx = SSL_CTX_new(method);
    if (ctx == NULL) {
        fprintf(stderr, "Error: SSL_CTX_new() failed\n");
        dump_errors();
        return 1;
    }

    /* test_sslapi frequently checks security levels */
    SSL_CTX_set_security_level(ctx, 1);

    ssl = SSL_new(ctx);
    if (ssl == NULL) {
        fprintf(stderr, "Error: SSL_new() failed\n");
        dump_errors();
        SSL_CTX_free(ctx);
        return 1;
    }

    /* Set up memory BIOs to ensure the SSL object is fully functional */
    rbio = BIO_new(BIO_s_mem());
    wbio = BIO_new(BIO_s_mem());
    SSL_set_bio(ssl, rbio, wbio);

    printf("Successfully created SSL and SSL_CTX objects.\n");

    SSL_free(ssl);
    SSL_CTX_free(ctx);

    printf("OK\n");
    return 0;
}