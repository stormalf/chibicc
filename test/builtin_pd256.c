// test___builtin_ia32_pd_pd256.c
// Compile: gcc -O2 -mavx test.c -o test && ./test

#include <immintrin.h>
#include <stdio.h>
#include <math.h>     // fabs()
#include <assert.h>

/* Helper: extract double lane i from __m256d */
static inline double get256d(__m256d v, int i) {
    double buf[4];
    _mm256_storeu_pd(buf, v);
    return buf[i];
}

int main(void) {
    /* ── Test 1: basic lane promotion ─────────────────────────── */
    __m128d src = _mm_set_pd(2.0, 1.0);   // lanes: [1.0, 2.0]

    __m256d dst = __builtin_ia32_pd_pd256(src);

    /* Lower 128 bits must equal src */
    assert(fabs(get256d(dst, 0) - 1.0) < 1e-15);
    assert(fabs(get256d(dst, 1) - 2.0) < 1e-15);
    /* Upper 128 bits are undefined — do NOT assert their values */

    /* ── Test 2: negative / subnormal values ───────────────────── */
    __m128d neg = _mm_set_pd(-0.0, -1.5e-308);
    __m256d neg256 = __builtin_ia32_pd_pd256(neg);
    assert(fabs(get256d(neg256, 0) - (-1.5e-308)) < 1e-320);
    assert(get256d(neg256, 1) == -0.0);

    /* ── Test 3: NaN / Inf passthrough ────────────────────────── */
    double inf = 1.0 / 0.0;
    double nan_val = 0.0 / 0.0;
    __m128d special = _mm_set_pd(inf, nan_val);
    __m256d sp256 = __builtin_ia32_pd_pd256(special);
    assert(isnan(get256d(sp256, 0)));    // lane 0: NaN
    assert(isinf(get256d(sp256, 1)));    // lane 1: +Inf

    /* ── Test 4: zero vector ──────────────────────────────────── */
    __m256d zero256 = __builtin_ia32_pd_pd256(_mm_setzero_pd());
    assert(get256d(zero256, 0) == 0.0);
    assert(get256d(zero256, 1) == 0.0);

    printf("All tests passed.\n");
    return 0;
}
