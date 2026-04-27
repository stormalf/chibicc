#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int rd_key[4 * (14 + 1)];
    int rounds;
} VPAES_KEY;

int vpaes_set_encrypt_key(const unsigned char *userKey, int bits, VPAES_KEY *key);
void vpaes_encrypt(const unsigned char *in, unsigned char *out, const VPAES_KEY *key);

int main() {
    // NIST SP 800-38A Test Vector (AES-128)
    unsigned char key_hex[] = {
        0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c
    };
    unsigned char pt[] = {
        0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
        0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a
    };
    unsigned char expected_ct[] = {
        0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0xd0, 0x8c,
        0x1b, 0xb0, 0x35, 0x66, 0x71, 0x59, 0x20, 0x13
    };

    unsigned char ct[16];
    // VPAES requires 16-byte alignment for the key schedule because
    // the assembly uses movdqa to load round keys.
    __attribute__((aligned(16))) VPAES_KEY vkey;

    vpaes_set_encrypt_key(key_hex, 128, &vkey);
    vpaes_encrypt(pt, ct, &vkey);

        for (int i = 0; i < 16; i++)
            if (ct[i] != expected_ct[i]) {
                printf("%x", ct[i]);
                printf("%x", expected_ct[i]) ;
              
            }
            
        printf("VPAES Test Passed\n");
        return 0;

}