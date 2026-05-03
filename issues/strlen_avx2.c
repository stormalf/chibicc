// test_pem_buf_corruption.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define PEM_BUFSIZE 1024
#define NTEST 1000

static void fill_pattern(unsigned char *p, size_t n, unsigned char seed) {
    for (size_t i = 0; i < n; i++)
        p[i] = seed ^ (unsigned char)i;
}

static int check_pattern(const unsigned char *p, size_t n, unsigned char seed) {
    for (size_t i = 0; i < n; i++) {
        unsigned char expected = seed ^ (unsigned char)i;
        if (p[i] != expected)
            return 0;
    }
    return 1;
}

static void test_pem_buf(const char *name, const unsigned char *data, size_t len) {
    BIO *bio = BIO_new(BIO_s_mem());
    assert(bio);

    int ret = PEM_write_bio(bio, name, NULL, data, len);
    if (ret <= 0) {
        printf("PEM_write_bio failed\n");
        ERR_print_errors_fp(stdout);
        exit(1);
    }

    BIO_free(bio);
}

static void test_corruption_detection() {
    unsigned char *buf = malloc(PEM_BUFSIZE * 8);
    assert(buf);

    for (int i = 0; i < NTEST; i++) {
        size_t len = (rand() % (PEM_BUFSIZE * 8 - 1)) + 1;

        fill_pattern(buf, len, (unsigned char)(i & 0xFF));

        test_pem_buf("TEST DATA", buf, len);

        // VERIFY ORIGINAL BUFFER WAS NOT CORRUPTED
        if (!check_pattern(buf, len, (unsigned char)(i & 0xFF))) {
            printf("BUFFER CORRUPTION DETECTED at iter=%d len=%zu\n", i, len);
            exit(1);
        }
    }

    free(buf);
}

static void test_large_allocation_pressure() {
    for (int i = 0; i < 500; i++) {
        unsigned char *buf = OPENSSL_malloc(PEM_BUFSIZE * 8);
        assert(buf);

        memset(buf, rand() & 0xFF, PEM_BUFSIZE * 8);

        PEM_write_bio(BIO_new(BIO_s_mem()), "PRESSURE", NULL, buf, PEM_BUFSIZE * 8);

        OPENSSL_free(buf);
    }
}

int main() {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    test_corruption_detection();
    test_large_allocation_pressure();

    printf("OK\n");
    return 0;
}
