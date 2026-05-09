

// test___builtin_ia32_ps_ps256.c
// Compile: gcc -O2 -mavx test.c -o test && ./test

#include <immintrin.h>
#include <stdio.h>
#include <math.h>     // fabsf(), isnanf(), isinff()
#include <assert.h>

/* Helper: extract float lane i from __m256 */
static inline float get256s(__m256 v, int i) {
    float buf[8];
    _mm256_storeu_ps(buf, v);
    return buf[i];
}

int main(void) {
    /* ── Test 1: basic lane promotion ─────────────────────────── */
    __m128 src = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f);
    // _mm_set_ps fills highest-to-lowest: lanes [1,2,3,4]

    __m256 dst = __builtin_ia32_ps_ps256(src);

    /* Lower 128 bits (lanes 0-3) must equal src */
    assert(fabsf(get256s(dst, 0) - 1.0f) < 1e-7f);
    assert(fabsf(get256s(dst, 1) - 2.0f) < 1e-7f);
    assert(fabsf(get256s(dst, 2) - 3.0f) < 1e-7f);
    assert(fabsf(get256s(dst, 3) - 4.0f) < 1e-7f);
    /* Upper 128 bits (lanes 4-7) are undefined — do NOT assert */

    /* ── Test 2: negative / subnormal values ───────────────────── */
    __m128 neg = _mm_set_ps(-0.0f, -1.0f, 1.4e-45f, -3.14f);
    __m256 neg256 = __builtin_ia32_ps_ps256(neg);
    assert(fabsf(get256s(neg256, 0) - (-3.14f)) < 1e-5f);   // lane 0
    assert(get256s(neg256, 1) == 1.4e-45f);                  // subnormal
    assert(fabsf(get256s(neg256, 2) - (-1.0f)) < 1e-7f);
    assert(get256s(neg256, 3) == -0.0f);                      // negative zero

    /* ── Test 3: NaN / Inf passthrough ────────────────────────── */
    float inf     = 1.0f / 0.0f;
    float nan_val = 0.0f / 0.0f;
    __m128 special = _mm_set_ps(inf, nan_val, -inf, 42.0f);
    __m256 sp256 = __builtin_ia32_ps_ps256(special);
    assert(fabsf(get256s(sp256, 0) - 42.0f) < 1e-7f);  // lane 0: 42.0
    assert(isinf(get256s(sp256, 1)) && get256s(sp256, 1) < 0); // -Inf
    assert(isnan(get256s(sp256, 2)));                    // NaN
    assert(isinf(get256s(sp256, 3)) && get256s(sp256, 3) > 0); // +Inf

    /* ── Test 4: zero vector ──────────────────────────────────── */
    __m256 zero256 = __builtin_ia32_ps_ps256(_mm_setzero_ps());
    assert(get256s(zero256, 0) == 0.0f);
    assert(get256s(zero256, 1) == 0.0f);
    assert(get256s(zero256, 2) == 0.0f);
    assert(get256s(zero256, 3) == 0.0f);

    /* ── Test 5: all-ones bit pattern ─────────────────────────── */
    __m128 ones = _mm_castsi128_ps(_mm_set1_epi32(0xFFFFFFFF));
    __m256 ones256 = __builtin_ia32_ps_ps256(ones);
    int ibuf[8];
    _mm256_storeu_si256((__m256i *)ibuf, _mm256_castps_si256(ones256));
    assert(ibuf[0] == (int)0xFFFFFFFF);
    assert(ibuf[1] == (int)0xFFFFFFFF);
    assert(ibuf[2] == (int)0xFFFFFFFF);
    assert(ibuf[3] == (int)0xFFFFFFFF);

    printf("All tests passed.\n");
    return 0;
}


