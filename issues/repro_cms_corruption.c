/*
 * repro_cms_corruption.c
 *
 * Reproduction for CMS signing corruption when compiled with chibicc.
 * Mimics: openssl cms -sign -md sha1 -signer smrsa1.pem -certfile smroot.pem
 */

#include <stdio.h>
#include <string.h>
#include <openssl/cms.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/bio.h>

int main(void) {
    const char *msg = "Content to be signed for CMS corruption test.\n";
    X509 *cert = NULL;
    EVP_PKEY *key = NULL;
    CMS_ContentInfo *cms = NULL;
    BIO *in = NULL, *certbio = NULL, *keybio = NULL, *out = NULL;
    int ret = 1;

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    printf("Loading signer certificate and key...\n");

    /* Using paths consistent with the OpenSSL source tree as used in your command */
    certbio = BIO_new_file("/home/stormalf/openssl/test/smime-certs/smrsa1.pem", "r");
    if (!certbio) {
        fprintf(stderr, "Error: Could not open smrsa1.pem\n");
        return 1;
    }
    cert = PEM_read_bio_X509(certbio, NULL, NULL, NULL);
    
    /* Rewind or reopen for the key (smrsa1.pem usually contains both) */
    BIO_reset(certbio);
    key = PEM_read_bio_PrivateKey(certbio, NULL, NULL, NULL);

    if (!cert || !key) {
        fprintf(stderr, "Error: Failed to load cert or key\n");
        ERR_print_errors_fp(stderr);
        goto end;
    }

    in = BIO_new_mem_buf(msg, -1);

    printf("Performing CMS_sign (SHA1)...\n");
    /* 
     * We specify CMS_DETACHED to match the typical CLI behavior.
     * The issue likely lies in the signature calculation or the 
     * ASN1 structure construction on the stack.
     */
    cms = CMS_sign(cert, key, NULL, in, CMS_DETACHED);
    if (!cms) {
        fprintf(stderr, "Error: CMS_sign failed\n");
        ERR_print_errors_fp(stderr);
        goto end;
    }

    /* Export to DER to check for encoding corruption */
    out = BIO_new(BIO_s_mem());
    if (!i2d_CMS_bio(out, cms)) {
        fprintf(stderr, "Error: i2d_CMS_bio (ASN.1 encoding) failed\n");
        ERR_print_errors_fp(stderr);
        goto end;
    }

    printf("Successfully signed. Testing verification of generated CMS object...\n");

    /* Verification logic */
    BIO_reset(in);
    STACK_OF(X509) *certs = sk_X509_new_null();
    X509_STORE *store = X509_STORE_new();
    
    /* In a real test we'd add the root, but for internal consistency check 
       CMS_NOCERTVERIFY is often enough to see if the signature itself is valid */
    if (CMS_verify(cms, certs, store, in, NULL, CMS_NOVERIFY) <= 0) {
        fprintf(stderr, "BUG REPRODUCED: CMS_verify failed on freshly signed content!\n");
        fprintf(stderr, "This indicates stack or register corruption during signing.\n");
        ERR_print_errors_fp(stderr);
        goto end;
    }

    printf("CMS Verification successful. No corruption detected in this run.\n");
    ret = 0;

end:
    CMS_ContentInfo_free(cms);
    BIO_free(in);
    BIO_free(certbio);
    BIO_free(out);
    X509_free(cert);
    EVP_PKEY_free(key);
    return ret;
}