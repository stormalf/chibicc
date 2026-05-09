/*
 * test_evp_encode_update_ia32cap.c
 *
 * Test case for EVP_EncodeUpdate exercising the HAS_IA32CAP_IS_64 branch.
 *
 * Compiled with:
 *   gcc -DHAS_IA32CAP_IS_64 -o test_evp_encode_update test_evp_encode_update_ia32cap.c -lssl -lcrypto
 *
 * Two sub-tests:
 *   1. AVX2 path  : OPENSSL_ia32cap_P[2] bit 5 SET   → encode_base64_avx2()
 *   2. scalar path: OPENSSL_ia32cap_P[2] bit 5 CLEAR → evp_encodeblock_int()
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <openssl/evp.h>
#include <immintrin.h>

#define  HAS_IA32CAP_IS_64  1
#define EVP_ENCODE_B64_LENGTH 48
#define EVP_ENCODE_CTX_NO_NEWLINES 1

void OPENSSL_cpuid_setup() { return ;};
/* ── capability word exposed by OpenSSL ────────────────────────────────── */
unsigned int OPENSSL_ia32cap_P[10];   /* 40 bytes, matches OpenSSL layout */
/* AVX2 is reported in OPENSSL_ia32cap_P[2] bit 5 (CPUID leaf 7, EBX bit 5)  */
#define AVX2_BIT  (1u << 5)
#define EVP_ENCODE_CTX_USE_SRP_ALPHABET 2

struct evp_Encode_Ctx_st {
    /* number saved in a partial encode/decode */
    int num;
    /* data to encode */
    unsigned char enc_data[80];
    /* number read on current line */
    int line_num;
    unsigned int flags;
};
typedef struct evp_Encode_Ctx_st EVP_ENCODE_CTX;

static const unsigned char data_bin2ascii[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
/* SRP uses a different base64 alphabet */
static const unsigned char srpdata_bin2ascii[65] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz./";
#define conv_bin2ascii(a, table) ((table)[(a) & 0x3f])

static const unsigned char base64_srp_bin2ascii_0[256] = {
    '0', '0', '0', '0', '1', '1', '1', '1', '2', '2', '2', '2', '3', '3', '3', '3',
    '4', '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7',
    '8', '8', '8', '8', '9', '9', '9', '9', 'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B',
    'C', 'C', 'C', 'C', 'D', 'D', 'D', 'D', 'E', 'E', 'E', 'E', 'F', 'F', 'F', 'F',
    'G', 'G', 'G', 'G', 'H', 'H', 'H', 'H', 'I', 'I', 'I', 'I', 'J', 'J', 'J', 'J',
    'K', 'K', 'K', 'K', 'L', 'L', 'L', 'L', 'M', 'M', 'M', 'M', 'N', 'N', 'N', 'N',
    'O', 'O', 'O', 'O', 'P', 'P', 'P', 'P', 'Q', 'Q', 'Q', 'Q', 'R', 'R', 'R', 'R',
    'S', 'S', 'S', 'S', 'T', 'T', 'T', 'T', 'U', 'U', 'U', 'U', 'V', 'V', 'V', 'V',
    'W', 'W', 'W', 'W', 'X', 'X', 'X', 'X', 'Y', 'Y', 'Y', 'Y', 'Z', 'Z', 'Z', 'Z',
    'a', 'a', 'a', 'a', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'c', 'd', 'd', 'd', 'd',
    'e', 'e', 'e', 'e', 'f', 'f', 'f', 'f', 'g', 'g', 'g', 'g', 'h', 'h', 'h', 'h',
    'i', 'i', 'i', 'i', 'j', 'j', 'j', 'j', 'k', 'k', 'k', 'k', 'l', 'l', 'l', 'l',
    'm', 'm', 'm', 'm', 'n', 'n', 'n', 'n', 'o', 'o', 'o', 'o', 'p', 'p', 'p', 'p',
    'q', 'q', 'q', 'q', 'r', 'r', 'r', 'r', 's', 's', 's', 's', 't', 't', 't', 't',
    'u', 'u', 'u', 'u', 'v', 'v', 'v', 'v', 'w', 'w', 'w', 'w', 'x', 'x', 'x', 'x',
    'y', 'y', 'y', 'y', 'z', 'z', 'z', 'z', '.', '.', '.', '.', '/', '/', '/', '/'
};

static const unsigned char base64_srp_bin2ascii_1[256] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/'
};

static const unsigned char base64_srp_bin2ascii_2[256] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
    'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '/'
};

static const unsigned char base64_std_bin2ascii_0[256] = {
    'A', 'A', 'A', 'A', 'B', 'B', 'B', 'B', 'C', 'C', 'C', 'C', 'D', 'D', 'D',
    'D', 'E', 'E', 'E', 'E', 'F', 'F', 'F', 'F', 'G', 'G', 'G', 'G', 'H', 'H',
    'H', 'H', 'I', 'I', 'I', 'I', 'J', 'J', 'J', 'J', 'K', 'K', 'K', 'K', 'L',
    'L', 'L', 'L', 'M', 'M', 'M', 'M', 'N', 'N', 'N', 'N', 'O', 'O', 'O', 'O',
    'P', 'P', 'P', 'P', 'Q', 'Q', 'Q', 'Q', 'R', 'R', 'R', 'R', 'S', 'S', 'S',
    'S', 'T', 'T', 'T', 'T', 'U', 'U', 'U', 'U', 'V', 'V', 'V', 'V', 'W', 'W',
    'W', 'W', 'X', 'X', 'X', 'X', 'Y', 'Y', 'Y', 'Y', 'Z', 'Z', 'Z', 'Z', 'a',
    'a', 'a', 'a', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'c', 'd', 'd', 'd', 'd',
    'e', 'e', 'e', 'e', 'f', 'f', 'f', 'f', 'g', 'g', 'g', 'g', 'h', 'h', 'h',
    'h', 'i', 'i', 'i', 'i', 'j', 'j', 'j', 'j', 'k', 'k', 'k', 'k', 'l', 'l',
    'l', 'l', 'm', 'm', 'm', 'm', 'n', 'n', 'n', 'n', 'o', 'o', 'o', 'o', 'p',
    'p', 'p', 'p', 'q', 'q', 'q', 'q', 'r', 'r', 'r', 'r', 's', 's', 's', 's',
    't', 't', 't', 't', 'u', 'u', 'u', 'u', 'v', 'v', 'v', 'v', 'w', 'w', 'w',
    'w', 'x', 'x', 'x', 'x', 'y', 'y', 'y', 'y', 'z', 'z', 'z', 'z', '0', '0',
    '0', '0', '1', '1', '1', '1', '2', '2', '2', '2', '3', '3', '3', '3', '4',
    '4', '4', '4', '5', '5', '5', '5', '6', '6', '6', '6', '7', '7', '7', '7',
    '8', '8', '8', '8', '9', '9', '9', '9', '+', '+', '+', '+', '/', '/', '/',
    '/'
};

static const unsigned char base64_std_bin2ascii_1[256] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
    't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '/', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', 'A', 'B', 'C',
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+',
    '/'
};

static const unsigned char base64_std_bin2ascii_2[256] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
    't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '+', '/', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3',
    '4', '5', '6', '7', '8', '9', '+', '/', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/', 'A', 'B', 'C',
    'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+',
    '/'
};


static const uint8_t shuffle_masks[16][16] = {
    { 0x80, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 0x80, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 0x80, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 0x80, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 0x80, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 0x80, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 0x80, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 0x80, 7, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 0x80, 8, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 0x80, 9, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x80, 10, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0x80, 11, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0x80, 12, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 0x80, 13, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0x80, 14 },
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0x80 }
};


static inline __m256i insert_newlines_by_mask(__m256i data, __m256i mask)
{
    __m256i newline = _mm256_set1_epi8('\n');

    return _mm256_or_si256(_mm256_and_si256(mask, newline),
        _mm256_andnot_si256(mask, data));
}

static inline size_t insert_nl_str8(const __m256i v0, uint8_t *output)
{
    __m256i shuffling_mask = _mm256_setr_epi8(0, 1, 2, 3, 4, 5, 6, 7, (char)0xFF,
        8, 9, 10, 11, 12, 13, 14,
        (char)0xFF, (char)0xFF, 0, 1, 2, 3, 4, 5, 6,
        7, (char)0xFF, 8, 9, 10, 11, 12);
    __m256i shuffled_4_bytes = _mm256_shuffle_epi8(v0, shuffling_mask);
    _mm256_storeu_si256((__m256i *)(output), shuffled_4_bytes);
    int8_t rem_1_L = _mm256_extract_epi8(v0, 15);
    int8_t rem_2_L_P1 = _mm256_extract_epi8(v0, 29);
    int16_t rem_2_L_P2 = _mm256_extract_epi16(v0, 15);
    uint8_t *out = output;

    memcpy(out + 16, &rem_1_L, sizeof(rem_1_L));
    memcpy(out + 32, &rem_2_L_P1, sizeof(rem_2_L_P1));
    memcpy(out + 32 + 1, &rem_2_L_P2, sizeof(rem_2_L_P2));

    output[8] = '\n';
    output[17] = '\n';
    output[26] = '\n';
    output[35] = '\n';

    out += 32 + 4;

    size_t written = (out - output);
    return written;
}

static inline __m256i lookup_pshufb_srp(__m256i input)
{
    const __m256i zero = _mm256_setzero_si256();
    const __m256i hi = _mm256_set1_epi8((char)0x80);
    __m256i invalid = _mm256_or_si256(_mm256_cmpgt_epi8(zero, input),
        _mm256_cmpgt_epi8(input,
            _mm256_set1_epi8(63)));
    __m256i idx = _mm256_setzero_si256();

    idx = _mm256_sub_epi8(idx, _mm256_cmpgt_epi8(input, _mm256_set1_epi8(9)));
    idx = _mm256_sub_epi8(idx, _mm256_cmpgt_epi8(input, _mm256_set1_epi8(35)));
    idx = _mm256_blendv_epi8(idx, _mm256_set1_epi8(3),
        _mm256_cmpeq_epi8(input, _mm256_set1_epi8(62)));
    idx = _mm256_blendv_epi8(idx, _mm256_set1_epi8(4),
        _mm256_cmpeq_epi8(input, _mm256_set1_epi8(63)));

    /* Zero-out invalid lanes via PSHUFB's high-bit mechanism */
    idx = _mm256_or_si256(idx, _mm256_and_si256(invalid, hi));

    const __m256i shift_LUT = _mm256_setr_epi8('0' - 0, 'A' - 10, 'a' - 36, '.' - 62, '/' - 63, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        '0' - 0, 'A' - 10, 'a' - 36, '.' - 62, '/' - 63, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0);

    __m256i shift = _mm256_shuffle_epi8(shift_LUT, idx);
    __m256i ascii = _mm256_add_epi8(shift, input);
    return ascii;
}


static __m256i lookup_pshufb_std(__m256i input)
{
    __m256i result = _mm256_subs_epu8(input, _mm256_set1_epi8(51));
    const __m256i less = _mm256_cmpgt_epi8(_mm256_set1_epi8(26), input);

    result = _mm256_or_si256(result, _mm256_and_si256(less, _mm256_set1_epi8(13)));
    __m256i shift_LUT = _mm256_setr_epi8('a' - 26, '0' - 52, '0' - 52, '0' - 52, '0' - 52,
        '0' - 52, '0' - 52,
        '0' - 52, '0' - 52, '0' - 52, '0' - 52, '+' - 62,
        '/' - 63, 'A', 0, 0,
        'a' - 26, '0' - 52, '0' - 52, '0' - 52, '0' - 52,
        '0' - 52, '0' - 52,
        '0' - 52, '0' - 52, '0' - 52, '0' - 52, '+' - 62,
        '/' - 63, 'A', 0, 0);

    result = _mm256_shuffle_epi8(shift_LUT, result);
    return _mm256_add_epi8(result, input);
}


static inline size_t insert_nl_str4(const __m256i v0, uint8_t *output)
{
    __m256i shuffling_mask = _mm256_setr_epi8(0, 1, 2, 3, (char)0xFF, 4, 5, 6,
        7, (char)0xFF, 8, 9, 10, 11, (char)0xFF, 12,
        (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF, 0, 1, 2, 3,
        (char)0xFF, 4, 5, 6, 7, (char)0xFF, 8, 9);
    __m256i mask_5_bytes = _mm256_setr_epi8(0, 0, 0, 0, (char)0xFF, 0, 0, 0, 0, (char)0xFF,
        0, 0, 0, 0, (char)0xFF, 0, 0, 0, 0, (char)0xFF,
        0, 0, 0, 0, (char)0xFF, 0, 0, 0, 0, (char)0xFF,
        0, 0);
    __m256i shuffled_4_bytes = _mm256_shuffle_epi8(v0, shuffling_mask);
    __m256i v0_w_nl = insert_newlines_by_mask(shuffled_4_bytes, mask_5_bytes);

    _mm256_storeu_si256((__m256i *)(output + 0), v0_w_nl);

    /* Handle cross-lane remainder logic */
    /* Without macros, _mm256_srli_si256 complains that the last arg must be an 8-bit immediate */
#define B_LANE 16 /* Bytes per lane */
#define N_RET_1_L 3 /* bytes "shifted out" of lane 0 */
#define N_RET_2_L (N_RET_1_L + 4) /* bytes "shifted out" of lane 1 */

    /* Bytes that were shifted out of lane 0 */
    __m256i rem_1_L = _mm256_srli_si256(v0, B_LANE - N_RET_1_L);

    /* Bytes that were shifted out of lane 1 */
    __m256i rem_2_L_P1 = _mm256_srli_si256(_mm256_slli_si256(_mm256_srli_si256(v0, B_LANE - N_RET_2_L),
                                               B_LANE - N_RET_1_L),
        B_LANE - 2);

    /* isolate the bytes that were shifted out of lane 1 */
    __m256i rem_2_L_P2 = _mm256_slli_si256(
        _mm256_srli_si256(v0,
            B_LANE - N_RET_2_L + N_RET_1_L),
        N_RET_1_L);

    __m256i rem_2_L = _mm256_or_si256(rem_2_L_P1, rem_2_L_P2);

    int32_t rem_1_L_ext = _mm256_extract_epi32(rem_1_L, 0);
    int64_t rem_2_L_ext = _mm256_extract_epi64(rem_2_L, 2);

    uint8_t *out = output + 16;
    memcpy(out, &rem_1_L_ext, sizeof(rem_1_L_ext));
    out += 3;
    *out++ = '\n';

    out = output + 32;
    memcpy(out, &rem_2_L_ext, sizeof(rem_2_L_ext));
    out += 2;
    *out++ = '\n';
    out += 4;
    *out++ = '\n';

    size_t written = (out - output);
    return written;
}


static inline __m256i shift_left_zeros(__m256i v, int n)
{
    switch (n) {
    case 0:
        return v;
    case 1:
        return _mm256_slli_si256(v, 1);
    case 2:
        return _mm256_slli_si256(v, 2);
    case 3:
        return _mm256_slli_si256(v, 3);
    case 4:
        return _mm256_slli_si256(v, 4);
    case 5:
        return _mm256_slli_si256(v, 5);
    case 6:
        return _mm256_slli_si256(v, 6);
    case 7:
        return _mm256_slli_si256(v, 7);
    case 8:
        return _mm256_slli_si256(v, 8);
    case 9:
        return _mm256_slli_si256(v, 9);
    case 10:
        return _mm256_slli_si256(v, 10);
    case 11:
        return _mm256_slli_si256(v, 11);
    case 12:
        return _mm256_slli_si256(v, 12);
    case 13:
        return _mm256_slli_si256(v, 13);
    case 14:
        return _mm256_slli_si256(v, 14);
    case 15:
        return _mm256_slli_si256(v, 15);
    case 16:
        return _mm256_setzero_si256();
    default:
        return _mm256_setzero_si256();
    }
}


static inline __m256i shift_right_zeros(__m256i v, int n)
{
    switch (n) {
    case 0:
        return v;
    case 1:
        return _mm256_srli_si256(v, 1);
    case 2:
        return _mm256_srli_si256(v, 2);
    case 3:
        return _mm256_srli_si256(v, 3);
    case 4:
        return _mm256_srli_si256(v, 4);
    case 5:
        return _mm256_srli_si256(v, 5);
    case 6:
        return _mm256_srli_si256(v, 6);
    case 7:
        return _mm256_srli_si256(v, 7);
    case 8:
        return _mm256_srli_si256(v, 8);
    case 9:
        return _mm256_srli_si256(v, 9);
    case 10:
        return _mm256_srli_si256(v, 10);
    case 11:
        return _mm256_srli_si256(v, 11);
    case 12:
        return _mm256_srli_si256(v, 12);
    case 13:
        return _mm256_srli_si256(v, 13);
    case 14:
        return _mm256_srli_si256(v, 14);
    case 15:
        return _mm256_srli_si256(v, 15);
    default:
        return _mm256_setzero_si256();
    }
}

static inline size_t insert_nl_gt16(const __m256i v0,
    uint8_t *output,
    int wrap_max, int *wrap_cnt)
{
    uint8_t *out = output;
    int wrap_rem = wrap_max - *wrap_cnt;
    _mm256_storeu_si256((__m256i *)(output), v0);

    if (wrap_rem > 32) {
        *wrap_cnt += 32;
        return 32;
    }

    __m256i all_ff_mask = _mm256_set1_epi8((char)0xFF);

    __m256i mask_second_lane = _mm256_setr_epi8(0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF,
        (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF,
        (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF,
        (char)0xFF, (char)0xFF, (char)0xFF, (char)0xFF);

    __m256i blended_0L = v0;
    int surplus_0 = wrap_rem < 16 ? 1 : 0;
    if (surplus_0 == 1) {
        __m256i shifted_0_L = shift_left_zeros(shift_right_zeros(v0, wrap_rem),
            wrap_rem + surplus_0);
        __m256i mask_shifted_0_L = shift_left_zeros(all_ff_mask, wrap_rem + surplus_0);
        __m256i mask = _mm256_or_si256(mask_shifted_0_L, mask_second_lane);
        __m256i shifted_1_L = shift_left_zeros(v0, 1);
        __m256i shifted = _mm256_blendv_epi8(shifted_0_L, shifted_1_L, mask);

        blended_0L = _mm256_blendv_epi8(v0, shifted, mask);
        _mm256_storeu_si256((__m256i *)(output), blended_0L);
        wrap_rem += wrap_max;
    }

    int surplus_1 = (wrap_rem >= 16 && wrap_rem < 32) ? 1 : 0;
    int last_of_1L = _mm256_extract_epi8(v0, 31);

    if (surplus_1 == 1) {
        uint16_t sec_last_of_1L = _mm256_extract_epi8(v0, 30);
        int wrap_rem_1 = wrap_rem - 16;
        __m256i shifted_1_L = shift_left_zeros(shift_right_zeros(v0, wrap_rem_1),
            wrap_rem_1 + surplus_0 + surplus_1);
        __m256i mask_shifted_1_L = shift_left_zeros(all_ff_mask, wrap_rem_1 + surplus_0 + surplus_1);
        __m256i mask = _mm256_and_si256(mask_second_lane, mask_shifted_1_L);
        __m256i blended_1L = _mm256_blendv_epi8(blended_0L, shifted_1_L, mask);
        _mm256_storeu_si256((__m256i *)(output), blended_1L);

        output[wrap_rem + surplus_0] = '\n';
        output[31 + surplus_0] = (uint8_t)sec_last_of_1L;
        output[31 + surplus_0 + surplus_1] = last_of_1L;
    }

    if (surplus_0 == 1) {
        output[wrap_rem - wrap_max] = '\n';
        output[16] = _mm256_extract_epi8(v0, 15);
        output[31 + surplus_0 + surplus_1] = last_of_1L;
    }

    *wrap_cnt = wrap_rem > 32 ? 32 - (wrap_rem - wrap_max) : 32 - wrap_rem;

    int nl_at_end = 0;
    if (*wrap_cnt == wrap_max || *wrap_cnt == 0) {
        *wrap_cnt = 0;
        output[32 + surplus_0 + surplus_1] = '\n';
        nl_at_end = 1;
    }

    out += 32 + surplus_0 + surplus_1 + nl_at_end;
    size_t written = (size_t)(out - output);

    return written;
}


static inline __m256i insert_line_feed32(__m256i input, int K)
{
    __m256i line_feed_vector = _mm256_set1_epi8('\n');
    __m128i identity = _mm_setr_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);

    if (K >= 16) {
        __m128i maskhi = _mm_loadu_si128((__m128i *)shuffle_masks[K - 16]);
        __m256i mask = _mm256_set_m128i(maskhi, identity);
        __m256i lf_pos = _mm256_cmpeq_epi8(mask, _mm256_set1_epi8((char)0x80));
        __m256i shuffled = _mm256_shuffle_epi8(input, mask);
        __m256i result = _mm256_blendv_epi8(shuffled, line_feed_vector, lf_pos);

        return result;
    }
    /* Shift input right by 1 byte */
    __m256i shift = _mm256_alignr_epi8(input, _mm256_permute2x128_si256(input, input, 0x21),
        15);
    input = _mm256_blend_epi32(input, shift, 0xF0);
    __m128i masklo = _mm_loadu_si128((__m128i *)shuffle_masks[K]);
    __m256i mask = _mm256_set_m128i(identity, masklo);
    __m256i lf_pos = _mm256_cmpeq_epi8(mask, _mm256_set1_epi8((char)0x80));
    __m256i shuffled = _mm256_shuffle_epi8(input, mask);
    __m256i result = _mm256_blendv_epi8(shuffled, line_feed_vector, lf_pos);
    return result;
}

static inline size_t ins_nl_gt32(__m256i v, uint8_t *out, int stride,
    int *wrap_cnt)
{
    const int until_nl = stride - *wrap_cnt;

    if (until_nl > 32) {
        _mm256_storeu_si256((__m256i *)out, v);

        *wrap_cnt += 32;
        return 32;
    }

    if (until_nl == 32) {
        _mm256_storeu_si256((__m256i *)out, v);

        out[32] = '\n';
        *wrap_cnt = 0;
        return 33;
    }

    const uint8_t last = (uint8_t)_mm256_extract_epi8(v, 31);
    const __m256i with_lf = insert_line_feed32(v, until_nl);
    _mm256_storeu_si256((__m256i *)out, with_lf);
    out[32] = last;

    *wrap_cnt = 32 - until_nl;
    return 33;
}


static inline size_t insert_nl_2nd_vec_stride_12(const __m256i v0,
    uint8_t *output,
    int dummy_stride,
    int *wrap_cnt)
{
    __m256i shuffling_mask = _mm256_setr_epi8(0, 1, 2, 3, (char)0xFF, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
        (char)0xFF,
        (char)0xFF, (char)0xFF, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, (char)0xFF,
        12);
    __m256i shuffled = _mm256_shuffle_epi8(v0, shuffling_mask);

    _mm256_storeu_si256((__m256i *)(output + 0), shuffled);

    int16_t rem_1_L_ext = _mm256_extract_epi16(v0, 7);
    int8_t rem_2_L_ext_P1 = _mm256_extract_epi8(v0, 29);
    int16_t rem_2_L_ext_P2 = _mm256_extract_epi16(v0, 15);

    uint8_t *out = output;
    out[4] = '\n';
    memcpy(out + 15, &rem_1_L_ext, sizeof(rem_1_L_ext));
    out[16 + 1] = '\n';
    memcpy(out + 15 + 17, &rem_2_L_ext_P1, sizeof(rem_2_L_ext_P1));
    out[16 + 14] = '\n';
    memcpy(out + 15 + 17 + 1, &rem_2_L_ext_P2, sizeof(rem_2_L_ext_P2));

    out += 32 + 3;
    *wrap_cnt = 4;

    size_t written = (out - output);
    return written;
}


static int evp_encodeblock_int_old(EVP_ENCODE_CTX *ctx, unsigned char *t,
    const unsigned char *f, int dlen)
{
    int i, ret = 0;
    unsigned long l;
    const unsigned char *table;

    if (ctx != NULL && (ctx->flags & EVP_ENCODE_CTX_USE_SRP_ALPHABET) != 0)
        table = srpdata_bin2ascii;
    else
        table = data_bin2ascii;

    for (i = dlen; i > 0; i -= 3) {
        if (i >= 3) {
            l = (((unsigned long)f[0]) << 16L) | (((unsigned long)f[1]) << 8L) | f[2];
            *(t++) = conv_bin2ascii(l >> 18L, table);
            *(t++) = conv_bin2ascii(l >> 12L, table);
            *(t++) = conv_bin2ascii(l >> 6L, table);
            *(t++) = conv_bin2ascii(l, table);
        } else {
            l = ((unsigned long)f[0]) << 16L;
            if (i == 2)
                l |= ((unsigned long)f[1] << 8L);

            *(t++) = conv_bin2ascii(l >> 18L, table);
            *(t++) = conv_bin2ascii(l >> 12L, table);
            *(t++) = (i == 1) ? '=' : conv_bin2ascii(l >> 6L, table);
            *(t++) = '=';
        }
        ret += 4;
        f += 3;
    }

    *t = '\0';
    return ret;
}


size_t evp_encodeblock_int(EVP_ENCODE_CTX *ctx, unsigned char *t,
    const unsigned char *f, int dlen, int *wrap_cnt)
{
    int i = 0;
    size_t ret = 0;
    uint8_t t1, t2, t3;
    const unsigned char *e0, *e1, *e2;
    int srp = (ctx != NULL
        && (ctx->flags & EVP_ENCODE_CTX_USE_SRP_ALPHABET) != 0);
    int wrap_cnt_by_input = *wrap_cnt / 4 * 3;
    const int ctx_length = (ctx != NULL) ? EVP_ENCODE_B64_LENGTH : 0;

    if (srp) {
        e0 = base64_srp_bin2ascii_0;
        e1 = base64_srp_bin2ascii_1;
        e2 = base64_srp_bin2ascii_2;
    } else {
        e0 = base64_std_bin2ascii_0;
        e1 = base64_std_bin2ascii_1;
        e2 = base64_std_bin2ascii_2;
    }

    if (ctx_length == 1) {
        while (i < dlen && ctx != NULL) {
            t1 = f[i];
            *(t++) = e0[t1];
            *(t++) = e1[(t1 & 0x03) << 4];
            *(t++) = '=';
            *(t++) = '=';
            *(t++) = '\n';

            ret += 5;
            i++;
        }

        *t = '\0';
        ret--;

        return ret;
    } else if (ctx_length % 3 != 0) {
        i = 0;
        int wrap_cnt_nm3 = 0;
        while (i + 2 < dlen) {
            if (ctx != NULL) {
                if ((wrap_cnt_nm3 < EVP_ENCODE_B64_LENGTH
                        && (wrap_cnt_nm3 + 3 + wrap_cnt_by_input) > EVP_ENCODE_B64_LENGTH)
                    && ((ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) == 0)) {

                    switch (EVP_ENCODE_B64_LENGTH % 3) {
                    case 0:
                        break;
                    case 1:
                        t1 = f[i];
                        *(t++) = e0[t1];
                        *(t++) = e1[(t1 & 0x03) << 4];
                        *(t++) = '=';
                        *(t++) = '=';

                        ret += 4;
                        i++;
                        break;
                    case 2:
                        t1 = f[i];
                        t2 = f[i + 1];
                        *(t++) = e0[t1];
                        *(t++) = e1[((t1 & 0x03) << 4) | ((t2 >> 4) & 0x0F)];
                        *(t++) = e2[(t2 & 0x0F) << 2];
                        *(t++) = '=';
                        i += 2;
                        ret += 4;
                        break;
                    }
                    *(t++) = '\n';
                    ret++;
                    wrap_cnt_nm3 = 0;
                }
            }

            if (ctx_length >= 4 && i + 2 < dlen) {
                t1 = f[i];
                t2 = f[i + 1];
                t3 = f[i + 2];
                *(t++) = e0[t1];
                *(t++) = e1[((t1 & 0x03) << 4) | ((t2 >> 4) & 0x0F)];
                *(t++) = e1[((t2 & 0x0F) << 2) | ((t3 >> 6) & 0x03)];
                *(t++) = e2[t3];
                ret += 4;
                wrap_cnt_nm3 += 3;
                i += 3;
            }
        }
    } else {
        for (i = 0; i + 2 < dlen; i += 3) {

            t1 = f[i];
            t2 = f[i + 1];
            t3 = f[i + 2];
            *(t++) = e0[t1];
            *(t++) = e1[((t1 & 0x03) << 4) | ((t2 >> 4) & 0x0F)];
            *(t++) = e1[((t2 & 0x0F) << 2) | ((t3 >> 6) & 0x03)];
            *(t++) = e2[t3];
            ret += 4;

            if (ctx != NULL) {
                if ((i + 3 + wrap_cnt_by_input) % EVP_ENCODE_B64_LENGTH == 0
                    && ((ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) == 0)
                    && EVP_ENCODE_B64_LENGTH % 3 == 0) {
                    *(t++) = '\n';
                    ret++;
                }
            }
        }
    }

    switch (dlen - i) {
    case 0:
        break;
    case 1:
        t1 = f[i];
        *(t++) = e0[t1];
        *(t++) = e1[(t1 & 0x03) << 4];
        *(t++) = '=';
        *(t++) = '=';

        ret += 4;

        if (ctx != NULL) {
            if ((i + 1 + wrap_cnt_by_input) % EVP_ENCODE_B64_LENGTH == 0
                && ((ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) == 0)
                && EVP_ENCODE_B64_LENGTH % 3 == 0) {
                *(t++) = '\n';
                ret++;
            }
        }

        break;
    case 2:
        t1 = f[i];
        t2 = f[i + 1];
        *(t++) = e0[t1];
        *(t++) = e1[((t1 & 0x03) << 4) | ((t2 >> 4) & 0x0F)];
        *(t++) = e2[(t2 & 0x0F) << 2];
        *(t++) = '=';
        ret += 4;

        if (ctx != NULL) {
            if ((i + 2 + wrap_cnt_by_input) % EVP_ENCODE_B64_LENGTH == 0
                && ((ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) == 0)
                && EVP_ENCODE_B64_LENGTH % 3 == 0) {
                *(t++) = '\n';
                ret++;
            }
        }
        break;
    }

    *t = '\0';

    return ret;
}



size_t encode_base64_avx2(EVP_ENCODE_CTX *ctx, unsigned char *dst,
    const unsigned char *src, int srclen, int ctx_length,
    int *final_wrap_cnt)
{
    const uint8_t *input = (const uint8_t *)src;
    uint8_t *out = (uint8_t *)dst;
    int i = 0;
    int stride = (ctx == NULL) ? 0 : ctx_length / 3 * 4;
    int wrap_cnt = 0;
    const int use_srp = (ctx != NULL
        && (ctx->flags & EVP_ENCODE_CTX_USE_SRP_ALPHABET) != 0);
    const __m256i shuf = _mm256_set_epi8(10, 11, 9, 10, 7, 8, 6, 7, 4, 5, 3, 4, 1, 2, 0, 1,
        10, 11, 9, 10, 7, 8, 6, 7, 4, 5, 3, 4, 1, 2, 0, 1);
    int base = 0;

    /* Process 96 bytes at a time */
    for (; i + 100 <= srclen; i += 96) {
        _mm_prefetch((const char *)(input + i + 192), _MM_HINT_T0);
        /*
         * Interleaved for each vector: load, shuffle, bit-split, lookup
         * before starting the next, giving the OoO engine independent work chains
         * across execution ports.
         */
        const __m128i lo0 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 0));
        const __m128i hi0 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 1));
        __m256i in0 = _mm256_shuffle_epi8(_mm256_set_m128i(hi0, lo0), shuf);
        const __m256i t0_0 = _mm256_and_si256(in0, _mm256_set1_epi32(0x0fc0fc00));
        const __m256i t1_0 = _mm256_mulhi_epu16(t0_0, _mm256_set1_epi32(0x04000040));
        const __m256i t2_0 = _mm256_and_si256(in0, _mm256_set1_epi32(0x003f03f0));
        const __m256i t3_0 = _mm256_mullo_epi16(t2_0, _mm256_set1_epi32(0x01000010));
        const __m256i input0 = _mm256_or_si256(t1_0, t3_0);

        const __m128i lo1 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 2));
        const __m128i hi1 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 3));
        __m256i in1 = _mm256_shuffle_epi8(_mm256_set_m128i(hi1, lo1), shuf);
        const __m256i t0_1 = _mm256_and_si256(in1, _mm256_set1_epi32(0x0fc0fc00));
        const __m256i t1_1 = _mm256_mulhi_epu16(t0_1, _mm256_set1_epi32(0x04000040));
        const __m256i t2_1 = _mm256_and_si256(in1, _mm256_set1_epi32(0x003f03f0));
        const __m256i t3_1 = _mm256_mullo_epi16(t2_1, _mm256_set1_epi32(0x01000010));
        const __m256i input1 = _mm256_or_si256(t1_1, t3_1);

        const __m128i lo2 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 4));
        const __m128i hi2 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 5));
        __m256i in2 = _mm256_shuffle_epi8(_mm256_set_m128i(hi2, lo2), shuf);
        const __m256i t0_2 = _mm256_and_si256(in2, _mm256_set1_epi32(0x0fc0fc00));
        const __m256i t1_2 = _mm256_mulhi_epu16(t0_2, _mm256_set1_epi32(0x04000040));
        const __m256i t2_2 = _mm256_and_si256(in2, _mm256_set1_epi32(0x003f03f0));
        const __m256i t3_2 = _mm256_mullo_epi16(t2_2, _mm256_set1_epi32(0x01000010));
        const __m256i input2 = _mm256_or_si256(t1_2, t3_2);

        const __m128i lo3 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 6));
        const __m128i hi3 = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3 * 7));
        __m256i in3 = _mm256_shuffle_epi8(_mm256_set_m128i(hi3, lo3), shuf);
        const __m256i t0_3 = _mm256_and_si256(in3, _mm256_set1_epi32(0x0fc0fc00));
        const __m256i t1_3 = _mm256_mulhi_epu16(t0_3, _mm256_set1_epi32(0x04000040));
        const __m256i t2_3 = _mm256_and_si256(in3, _mm256_set1_epi32(0x003f03f0));
        const __m256i t3_3 = _mm256_mullo_epi16(t2_3, _mm256_set1_epi32(0x01000010));
        const __m256i input3 = _mm256_or_si256(t1_3, t3_3);

        __m256i vec0;
        __m256i vec1;
        __m256i vec2;
        __m256i vec3;

        if (use_srp) {
            vec0 = lookup_pshufb_srp(input0);
            vec1 = lookup_pshufb_srp(input1);
            vec2 = lookup_pshufb_srp(input2);
            vec3 = lookup_pshufb_srp(input3);

        } else {
            vec0 = lookup_pshufb_std(input0);
            vec1 = lookup_pshufb_std(input1);
            vec2 = lookup_pshufb_std(input2);
            vec3 = lookup_pshufb_std(input3);
        }

        if (stride == 0) {
            _mm256_storeu_si256((__m256i *)out, vec0);

            out += 32;
            _mm256_storeu_si256((__m256i *)out, vec1);

            out += 32;
            _mm256_storeu_si256((__m256i *)out, vec2);

            out += 32;
            _mm256_storeu_si256((__m256i *)out, vec3);

            out += 32;
        } else if (stride == 64) {
            _mm256_storeu_si256((__m256i *)out, vec0);

            out += 32;
            _mm256_storeu_si256((__m256i *)out, vec1);

            out += 32;
            *(out++) = '\n';

            _mm256_storeu_si256((__m256i *)out, vec2);
            out += 32;

            _mm256_storeu_si256((__m256i *)out, vec3);
            out += 32;

            *(out++) = '\n';
        } else if (stride == 4) {
            int out_idx = 0;

            out_idx += (int)insert_nl_str4(vec0, out + out_idx);
            out_idx += (int)insert_nl_str4(vec1, out + out_idx);
            out_idx += (int)insert_nl_str4(vec2, out + out_idx);
            out_idx += (int)insert_nl_str4(vec3, out + out_idx);

            out += out_idx;
        } else if (stride == 8) {

            out += insert_nl_str8(vec0, out);
            out += insert_nl_str8(vec1, out);
            out += insert_nl_str8(vec2, out);
            out += insert_nl_str8(vec3, out);

        } else if (stride == 12) {
            switch (base) {
            case 0:

                out += insert_nl_gt16(vec0, out, stride, &wrap_cnt);
                out += insert_nl_2nd_vec_stride_12(vec1, out, stride, &wrap_cnt);
                out += insert_nl_gt16(vec2, out, stride, &wrap_cnt);
                out += insert_nl_gt16(vec3, out, stride, &wrap_cnt);
                break;
            case 1:
                out += insert_nl_2nd_vec_stride_12(vec0, out, stride, &wrap_cnt);
                out += insert_nl_gt16(vec1, out, stride, &wrap_cnt);
                out += insert_nl_gt16(vec2, out, stride, &wrap_cnt);
                out += insert_nl_2nd_vec_stride_12(vec3, out, stride, &wrap_cnt);
                break;
            default: /* base == 2 */
                out += insert_nl_gt16(vec0, out, stride, &wrap_cnt);
                out += insert_nl_gt16(vec1, out, stride, &wrap_cnt);
                out += insert_nl_2nd_vec_stride_12(vec2, out, stride, &wrap_cnt);
                out += insert_nl_gt16(vec3, out, stride, &wrap_cnt);
                break;
            }

            if (++base == 3)
                base = 0;
        } else if (stride >= 32) {
            out += ins_nl_gt32(vec0, out, stride, &wrap_cnt);
            out += ins_nl_gt32(vec1, out, stride, &wrap_cnt);
            out += ins_nl_gt32(vec2, out, stride, &wrap_cnt);
            out += ins_nl_gt32(vec3, out, stride, &wrap_cnt);
        } else if (stride >= 16) {
            out += insert_nl_gt16(vec0, out, stride, &wrap_cnt);
            out += insert_nl_gt16(vec1, out, stride, &wrap_cnt);
            out += insert_nl_gt16(vec2, out, stride, &wrap_cnt);
            out += insert_nl_gt16(vec3, out, stride, &wrap_cnt);
        }
    }

    if (stride == 0) {
        for (; i + 28 <= srclen; i += 24) {
            /* lo = [xxxx|DDDC|CCBB|BAAA] */
            /* hi = [xxxx|HHHG|GGFF|FEEE] */
            const __m128i lo = _mm_loadu_si128((const __m128i *)(input + i));
            const __m128i hi = _mm_loadu_si128((const __m128i *)(input + i + 4 * 3));
            /*
             * bytes from groups A, B and C are needed in separate 32-bit lanes
             * in = [0HHH|0GGG|0FFF|0EEE[0DDD|0CCC|0BBB|0AAA]
             */
            __m256i in = _mm256_shuffle_epi8(_mm256_set_m128i(hi, lo), shuf);
            const __m256i t0 = _mm256_and_si256(in, _mm256_set1_epi32(0x0fc0fc00));
            const __m256i t1 = _mm256_mulhi_epu16(t0, _mm256_set1_epi32(0x04000040));
            const __m256i t2 = _mm256_and_si256(in, _mm256_set1_epi32(0x003f03f0));
            const __m256i t3 = _mm256_mullo_epi16(t2, _mm256_set1_epi32(0x01000010));
            const __m256i indices = _mm256_or_si256(t1, t3);
            _mm256_storeu_si256((__m256i *)out, (use_srp ? lookup_pshufb_srp : lookup_pshufb_std)(indices));

            out += 32;
        }
    }
    *final_wrap_cnt = wrap_cnt;

    if (stride >= 32 && wrap_cnt == stride) {
        wrap_cnt = 0;
        *out++ = '\n';
    }

    return (size_t)(out - (uint8_t *)dst) + evp_encodeblock_int(ctx, out, src + i, srclen - i, final_wrap_cnt);
}


int EVP_EncodeUpdate(EVP_ENCODE_CTX *ctx, unsigned char *out, int *outl,
    const unsigned char *in, int inl)
{
    int i;
    size_t j;
    size_t total = 0;

    *outl = 0;
    if (inl <= 0)
        return 0;
    assert(EVP_ENCODE_B64_LENGTH <= (int)sizeof(ctx->enc_data));
    if (EVP_ENCODE_B64_LENGTH - ctx->num > inl) {
        memcpy(&(ctx->enc_data[ctx->num]), in, inl);
        ctx->num += inl;
        return 1;
    }
    if (ctx->num != 0) {
        i = EVP_ENCODE_B64_LENGTH - ctx->num;
        memcpy(&(ctx->enc_data[ctx->num]), in, i);
        in += i;
        inl -= i;
        int wrap_cnt = 0;
        j = evp_encodeblock_int(ctx, out, ctx->enc_data, EVP_ENCODE_B64_LENGTH,
            &wrap_cnt);
        ctx->num = 0;
        out += j;
        total = j;
        *out = '\0';
    }
    int wrap_cnt = 0;
    if (EVP_ENCODE_B64_LENGTH % 3 != 0) {
        j = evp_encodeblock_int(ctx, out, in, inl - (inl % EVP_ENCODE_B64_LENGTH),
            &wrap_cnt);
    } else {
#if defined(__AVX2__)
        const int newlines = !(ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) ? EVP_ENCODE_B64_LENGTH : 0;

        j = encode_base64_avx2(ctx,
            (unsigned char *)out,
            (const unsigned char *)in,
            inl - (inl % EVP_ENCODE_B64_LENGTH), newlines, &wrap_cnt);
#elif defined(HAS_IA32CAP_IS_64)
        if ((OPENSSL_ia32cap_P[2] & (1u << 5)) != 0) {
            const int newlines = !(ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) ? EVP_ENCODE_B64_LENGTH : 0;

            j = encode_base64_avx2(ctx,
                (unsigned char *)out,
                (const unsigned char *)in,
                inl - (inl % EVP_ENCODE_B64_LENGTH), newlines, &wrap_cnt);
        } else {
            j = evp_encodeblock_int(ctx, out, in, inl - (inl % EVP_ENCODE_B64_LENGTH),
                &wrap_cnt);
        }
#else
        j = evp_encodeblock_int(ctx, out, in, inl - (inl % EVP_ENCODE_B64_LENGTH),
            &wrap_cnt);
#endif
    }
    in += inl - (inl % EVP_ENCODE_B64_LENGTH);
    inl -= inl - (inl % EVP_ENCODE_B64_LENGTH);
    out += j;
    total += j;
    if ((ctx->flags & EVP_ENCODE_CTX_NO_NEWLINES) == 0 && EVP_ENCODE_B64_LENGTH % 3 != 0) {
        *(out++) = '\n';
        total++;
    }
    *out = '\0';
    if (total > INT_MAX) {
        /* Too much output data! */
        *outl = 0;
        return 0;
    }
    if (inl != 0)
        memcpy(&(ctx->enc_data[0]), in, inl);
    ctx->num = inl;
    *outl = (int)total;

    return 1;
}

/* ── helpers ────────────────────────────────────────────────────────────── */
int EVP_EncodeBlock(unsigned char *t, const unsigned char *f, int dlen)
{
    int wrap_cnt = 0;

#if defined(__AVX2__)
    return (int)encode_base64_avx2(NULL, t, f, dlen, 0, &wrap_cnt);
#elif defined(HAS_IA32CAP_IS_64)
    if ((OPENSSL_ia32cap_P[2] & (1u << 5)) != 0)
        return (int)encode_base64_avx2(NULL, t, f, dlen, 0, &wrap_cnt);
    else
        return (int)evp_encodeblock_int(NULL, t, f, dlen, &wrap_cnt);
#else
    return (int)evp_encodeblock_int(NULL, t, f, dlen, &wrap_cnt);
#endif
}

/*
 * base64_decode_and_compare
 * Decodes the base64 string produced by EVP_EncodeUpdate / EVP_EncodeFinal
 * and verifies it matches the original plaintext.
 */
static int base64_round_trip_ok(const unsigned char *encoded, int enc_len,
                                const unsigned char *original, int orig_len)
{
    EVP_ENCODE_CTX *dctx = EVP_ENCODE_CTX_new();
    if (!dctx) return 0;

    unsigned char *decoded = malloc(enc_len + 4);
    if (!decoded) { EVP_ENCODE_CTX_free(dctx); return 0; }

    int dec_total = 0, n = 0;
    EVP_DecodeInit(dctx);
    EVP_DecodeUpdate(dctx, decoded, &n, encoded, enc_len);
    dec_total = n;
    EVP_DecodeFinal(dctx, decoded + dec_total, &n);
    dec_total += n;
    EVP_ENCODE_CTX_free(dctx);

    int ok = (dec_total == orig_len) &&
             (memcmp(decoded, original, orig_len) == 0);
    free(decoded);
    return ok;
}

/*
 * run_encode_test
 * Drives EVP_EncodeUpdate + EVP_EncodeFinal on `in`/`inl`,
 * prints the result, and validates the round-trip.
 * Returns 1 on success, 0 on failure.
 */
static int run_encode_test(const char *label,
                           const unsigned char *in, int inl,
                           int use_newlines)
{
    /* Output buffer: base64 expands ≤ 4/3 * inl, plus newlines + slop */
    int out_buf_size = ((inl / 3) + 2) * 4 + (inl / 48) + 64;
    unsigned char *out = calloc(1, out_buf_size);
    if (!out) return 0;

    EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
    if (!ctx) { free(out); return 0; }

    if (!use_newlines)
        /* EVP_EncodeInit always sets newlines; clear the flag manually */
        EVP_ENCODE_CTX_free(ctx),
        ctx = EVP_ENCODE_CTX_new(),   /* reinit */
        /* set NO_NEWLINES via the public flag after init */
        (void)0;   /* flag set below */

    EVP_EncodeInit(ctx);

    if (!use_newlines) {
        /*
         * EVP_ENCODE_CTX_no_newlines() is OpenSSL 3.x.
         * For older trees, cast and set the flag directly.
         * Adjust to your OpenSSL version:
         */
#ifdef EVP_ENCODE_CTX_NO_NEWLINES
        /* public API (OpenSSL 3) */
        ctx->flags |= EVP_ENCODE_CTX_NO_NEWLINES;
#endif
    }

    int outl = 0, total = 0;
    int ret = EVP_EncodeUpdate(ctx, out, &outl, in, inl);
    total = outl;

    unsigned char final_buf[8];
    int final_len = 0;
    EVP_EncodeFinal(ctx, final_buf, &final_len);
    if (final_len > 0)
        memcpy(out + total, final_buf, final_len);
    total += final_len;

    EVP_ENCODE_CTX_free(ctx);

    printf("[%s] EVP_EncodeUpdate returned %d, total encoded bytes = %d\n",
           label, ret, total);
    printf("[%s] Encoded output:\n%.*s\n", label, total, out);

    int ok = base64_round_trip_ok(out, total, in, inl);
    printf("[%s] Round-trip decode: %s\n\n", label, ok ? "PASS" : "FAIL");

    free(out);
    return ok;
}

/* ── main ───────────────────────────────────────────────────────────────── */
int main(void)
{
    int all_pass = 1;

    /*
     * Build input that is large enough to exercise the main encoding loop
     * (needs to exceed EVP_ENCODE_B64_LENGTH = 48 bytes so that the
     *  inner block-processing branch is reached).
     *
     * Use 192 bytes (= 4 × 48) so every alignment case is covered and
     * the AVX2 / scalar paths each process multiple full blocks.
     */
    unsigned char input[192];
    for (int i = 0; i < (int)sizeof(input); i++)
        input[i] = (unsigned char)(i & 0xFF);

    /* ── sub-test 1 : force AVX2 path ───────────────────────────────── */
    printf("=== Sub-test 1: HAS_IA32CAP_IS_64, AVX2 bit SET (encode_base64_avx2) ===\n");
    unsigned int saved_cap = OPENSSL_ia32cap_P[2];
     if ((OPENSSL_ia32cap_P[2] & (1u << 5)) == 0) {
    OPENSSL_ia32cap_P[2] |= AVX2_BIT;          /* set bit 5 */

    all_pass &= run_encode_test("AVX2-path, with-newlines",    input, sizeof(input), 1);
    all_pass &= run_encode_test("AVX2-path, no-newlines",      input, sizeof(input), 0);

    /* ── sub-test 2 : force scalar path ─────────────────────────────── */
    printf("=== Sub-test 2: HAS_IA32CAP_IS_64, AVX2 bit CLEAR (evp_encodeblock_int) ===\n");
    OPENSSL_ia32cap_P[2] &= ~AVX2_BIT;         /* clear bit 5 */

    all_pass &= run_encode_test("scalar-path, with-newlines",  input, sizeof(input), 1);
    all_pass &= run_encode_test("scalar-path, no-newlines",    input, sizeof(input), 0);

    /* restore capability word */
    OPENSSL_ia32cap_P[2] = saved_cap;

    /* ── sub-test 3 : partial block (ctx->num carry-over path) ──────── */
    printf("=== Sub-test 3: partial-block carry-over (num != 0 path) ===\n");
    /*
     * Feed data in two chunks so that ctx->num is non-zero on the
     * second call, exercising the memcpy + encode of the partial block.
     */
    {
        unsigned char out[512];
        int outl = 0, total = 0;
        EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
        EVP_EncodeInit(ctx);

        /* First call: 20 bytes → stored in ctx->enc_data, ctx->num = 20 */
        OPENSSL_ia32cap_P[2] |= AVX2_BIT;
        int r1 = EVP_EncodeUpdate(ctx, out, &outl, input, 20);
        total += outl;
        printf("[partial-block] first call (20 bytes): ret=%d outl=%d\n", r1, outl);

        /* Second call: 172 bytes → triggers the ctx->num != 0 flush */
        int r2 = EVP_EncodeUpdate(ctx, out + total, &outl, input + 20, 172);
        total += outl;
        printf("[partial-block] second call (172 bytes): ret=%d outl=%d\n", r2, outl);

        int final_len = 0;
        EVP_EncodeFinal(ctx, out + total, &final_len);
        total += final_len;
        EVP_ENCODE_CTX_free(ctx);
        OPENSSL_ia32cap_P[2] = saved_cap;

        int ok = base64_round_trip_ok(out, total, input, sizeof(input));
        printf("[partial-block] Round-trip decode: %s\n\n", ok ? "PASS" : "FAIL");
        all_pass &= ok;
    }
     }
    printf("==============================\n");
    printf("Overall result: %s\n", all_pass ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return all_pass ? 0 : 1;
}
