

// test___builtin_ia32_psllqi256.c
// Compile: gcc -O2 -mavx2 test.c -o test && ./test

#include <immintrin.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/* Helper: extract uint64 lane i (0-3) from __m256i */
static inline uint64_t get64(__m256i v, int i) {
    uint64_t buf[4];
    _mm256_storeu_si256((__m256i *)buf, v);
    return buf[i];
}

int main(void) {
    /* ── Test 1: shift by 1 ────────────────────────────────────── */
    // 0x4000000000000000 << 1 == 0x8000000000000000
    __m256i a = _mm256_set1_epi64x((int64_t)0x4000000000000000ULL);
    __m256i r1 = __builtin_ia32_psllqi256(a, 1);
    assert(get64(r1, 0) == 0x8000000000000000ULL);
    assert(get64(r1, 1) == 0x8000000000000000ULL);
    assert(get64(r1, 2) == 0x8000000000000000ULL);
    assert(get64(r1, 3) == 0x8000000000000000ULL);

    /* ── Test 2: shift by 4 (nibble boundary) ──────────────────── */
    // 0x0DEADBEEFCAFEBAB << 4 == 0xDEADBEEFCAFEBAB0
    __m256i b = _mm256_set1_epi64x((int64_t)0x0DEADBEEFCAFEBABULL);
    __m256i r4 = __builtin_ia32_psllqi256(b, 4);
    assert(get64(r4, 0) == 0xDEADBEEFCAFEBAB0ULL);
    assert(get64(r4, 3) == 0xDEADBEEFCAFEBAB0ULL);

    /* ── Test 3: shift by 63 (single bit survives at MSB) ──────── */
    __m256i c = _mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFFULL);
    __m256i r63 = __builtin_ia32_psllqi256(c, 63);
    assert(get64(r63, 0) == 0x8000000000000000ULL);
    assert(get64(r63, 1) == 0x8000000000000000ULL);
    assert(get64(r63, 2) == 0x8000000000000000ULL);
    assert(get64(r63, 3) == 0x8000000000000000ULL);

    /* ── Test 4: shift by 64 zeroes every lane ─────────────────── */
    __m256i r64 = __builtin_ia32_psllqi256(c, 64);
    assert(get64(r64, 0) == 0ULL);
    assert(get64(r64, 1) == 0ULL);
    assert(get64(r64, 2) == 0ULL);
    assert(get64(r64, 3) == 0ULL);

    /* ── Test 5: shift by 0 is identity ────────────────────────── */
    __m256i d = _mm256_set_epi64x(
        (int64_t)0xAAAAAAAAAAAAAAAAULL,
        (int64_t)0xBBBBBBBBBBBBBBBBULL,
        (int64_t)0xCCCCCCCCCCCCCCCCULL,
        (int64_t)0xDDDDDDDDDDDDDDDDULL
    );
    __m256i r0 = __builtin_ia32_psllqi256(d, 0);
    assert(get64(r0, 0) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r0, 1) == 0xCCCCCCCCCCCCCCCCULL);
    assert(get64(r0, 2) == 0xBBBBBBBBBBBBBBBBULL);
    assert(get64(r0, 3) == 0xAAAAAAAAAAAAAAAAULL);

    /* ── Test 6: LSB becomes 0 (zeros shifted in from LSB) ─────── */
    // Confirms this is a left shift, not a rotate — low bits drain to 0
    __m256i e = _mm256_set1_epi64x((int64_t)0xFFFFFFFFFFFFFFFFULL);
    __m256i r_lsb = __builtin_ia32_psllqi256(e, 1);
    assert(get64(r_lsb, 0) == 0xFFFFFFFFFFFFFFFEULL);
    assert(get64(r_lsb, 3) == 0xFFFFFFFFFFFFFFFEULL);

    /* ── Test 7: inverse of psrlqi256 by 4 ─────────────────────── */
    // round-trip: (x >> 4) << 4 masks the low nibble of each lane
    __m256i f = _mm256_set1_epi64x((int64_t)0x123456789ABCDEF0ULL);
    __m256i shifted_r = __builtin_ia32_psrlqi256(f, 4);
    __m256i round_trip = __builtin_ia32_psllqi256(shifted_r, 4);
    // low nibble (0xF0 >> 4 = 0x0F, 0x0F << 4 = 0xF0) wait — low nibble
    // of original is 0x0; round-trip should restore all but the lost nibble
    assert(get64(round_trip, 0) == 0x123456789ABCDEF0ULL);
    assert(get64(round_trip, 3) == 0x123456789ABCDEF0ULL);

    /* ── Test 8: lanes are independent ─────────────────────────── */
    __m256i g = _mm256_set_epi64x(
        (int64_t)0x0000000000000001ULL,  // lane 3
        (int64_t)0x0000000000000002ULL,  // lane 2
        (int64_t)0x0000000000000004ULL,  // lane 1
        (int64_t)0x0000000000000008ULL   // lane 0
    );
    __m256i r_ind = __builtin_ia32_psllqi256(g, 4);
    assert(get64(r_ind, 0) == 0x0000000000000080ULL);
    assert(get64(r_ind, 1) == 0x0000000000000040ULL);
    assert(get64(r_ind, 2) == 0x0000000000000020ULL);
    assert(get64(r_ind, 3) == 0x0000000000000010ULL);

    printf("All tests passed.\n");
    return 0;
}


