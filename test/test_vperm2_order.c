#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

int main() {
    int32_t sa[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int32_t sb[8] = {9, 10, 11, 12, 13, 14, 15, 16};
    __m256i a = _mm256_loadu_si256((__m256i*)sa);
    __m256i b = _mm256_loadu_si256((__m256i*)sb);
    __m256i r = _mm256_permute2x128_si256(a, b, 0x20); // low=a_low, high=b_low
    int32_t out[8];
    memcpy(out, &r, 32);
    printf("out[4]=%d (expected 9)\n", out[4]);
    if (out[4] == 9) printf("SUCCESS\n");
    else printf("FAILURE\n");
    return 0;
}
