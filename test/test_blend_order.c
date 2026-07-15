#include <immintrin.h>
#include <stdio.h>

int main() {
    __m256d x = _mm256_set_pd(1.0, 2.0, 3.0, 4.0); // {4, 3, 2, 1}
    __m256d y = _mm256_set_pd(5.0, 6.0, 7.0, 8.0); // {8, 7, 6, 5}
    __m256d z = _mm256_blend_pd(x, y, 0x01); // should take y[0] = 8.0, x[1..3]
    double out[4];
    _mm256_storeu_pd(out, z);
    printf("out[0]=%f (expected 8.0)\n", out[0]);
    if (out[0] == 8.0) printf("SUCCESS\n");
    else printf("FAILURE\n");
    return 0;
}
