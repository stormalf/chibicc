#include <openssl/bn.h>
#include <stdio.h>
#include <string.h>

int main() {
    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *r = BN_new();

    unsigned char buf1[32];
    unsigned char buf2[32];

    memset(buf1, 0x11, sizeof(buf1));
    memset(buf2, 0x22, sizeof(buf2));

    // initial allocation
    BN_bin2bn(buf1, sizeof(buf1), a);
    BN_bin2bn(buf2, sizeof(buf2), b);

    for (int i = 0; i < 800000; i++) {

        // FORCE reuse: overwrite same BN objects repeatedly
        buf1[0] ^= (unsigned char)i;
        buf2[0] ^= (unsigned char)(i >> 1);

        BN_bin2bn(buf1, sizeof(buf1), a);

        BN_bin2bn(buf2, sizeof(buf2), b);

                // heap pressure to amplify allocator reuse effects


        // force multiple internal BN_CTX allocations/reuse
        BN_CTX_start(ctx);

        // trigger multiplication path (bn_mul_words / fixed_top)
        BN_mul(r, a, b, ctx);
        BN_mod(r, a, b, ctx);  
        BN_add(r, a, b);
        BN_lshift(r, a, 1);        
        BN_cmp(a, b);   
        BN_mul(r, a, b, ctx);
        BN_CTX_end(ctx);

        // occasionally reset top behavior via re-init
        if ((i % 1000) == 0) {
            BN_zero(r);
        }

    }

    char *s = BN_bn2hex(r);
    printf("result = %s\n", s);

    OPENSSL_free(s);
    BN_free(a);
    BN_free(b);
    BN_free(r);
    BN_CTX_free(ctx);

    return 0;
}
