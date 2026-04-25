

// test___builtin_ia32_permdi256.c
// Compile: gcc -O2 -mavx2 test.c -o test && ./test
//
// __builtin_ia32_permdi256(src, imm8) == _mm256_permute4x64_epi64(src, imm8)
// The 8-bit immediate encodes four 2-bit selectors, one per output lane:
//   bits [1:0] -> dst lane 0 source
//   bits [3:2] -> dst lane 1 source
//   bits [5:4] -> dst lane 2 source
//   bits [7:6] -> dst lane 3 source
// Each 2-bit field picks a lane from src (0-3).

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
    /* Source vector with four distinct sentinel values per lane:
       lane 0 = 0xAAAA…, lane 1 = 0xBBBB…,
       lane 2 = 0xCCCC…, lane 3 = 0xDDDD…              */
    __m256i src = _mm256_set_epi64x(
        (int64_t)0xDDDDDDDDDDDDDDDDULL,  // lane 3
        (int64_t)0xCCCCCCCCCCCCCCCCULL,  // lane 2
        (int64_t)0xBBBBBBBBBBBBBBBBULL,  // lane 1
        (int64_t)0xAAAAAAAAAAAAAAAAULL   // lane 0
    );

    /* ── Test 1: identity  imm8 = 0b11_10_01_00 = 0xE4 ─────────── */
    // dst[0]=src[0], dst[1]=src[1], dst[2]=src[2], dst[3]=src[3]
    __m256i r_id = __builtin_ia32_permdi256(src, 0xE4);
    assert(get64(r_id, 0) == 0xAAAAAAAAAAAAAAAAULL);
    assert(get64(r_id, 1) == 0xBBBBBBBBBBBBBBBBULL);
    assert(get64(r_id, 2) == 0xCCCCCCCCCCCCCCCCULL);
    assert(get64(r_id, 3) == 0xDDDDDDDDDDDDDDDDULL);

    /* ── Test 2: full reverse  imm8 = 0b00_01_10_11 = 0x1B ──────── */
    // dst[0]=src[3], dst[1]=src[2], dst[2]=src[1], dst[3]=src[0]
    __m256i r_rev = __builtin_ia32_permdi256(src, 0x1B);
    assert(get64(r_rev, 0) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_rev, 1) == 0xCCCCCCCCCCCCCCCCULL);
    assert(get64(r_rev, 2) == 0xBBBBBBBBBBBBBBBBULL);
    assert(get64(r_rev, 3) == 0xAAAAAAAAAAAAAAAAULL);

    /* ── Test 3: broadcast lane 0  imm8 = 0b00_00_00_00 = 0x00 ──── */
    __m256i r_b0 = __builtin_ia32_permdi256(src, 0x00);
    assert(get64(r_b0, 0) == 0xAAAAAAAAAAAAAAAAULL);
    assert(get64(r_b0, 1) == 0xAAAAAAAAAAAAAAAAULL);
    assert(get64(r_b0, 2) == 0xAAAAAAAAAAAAAAAAULL);
    assert(get64(r_b0, 3) == 0xAAAAAAAAAAAAAAAAULL);

    /* ── Test 4: broadcast lane 3  imm8 = 0b11_11_11_11 = 0xFF ──── */
    __m256i r_b3 = __builtin_ia32_permdi256(src, 0xFF);
    assert(get64(r_b3, 0) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_b3, 1) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_b3, 2) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_b3, 3) == 0xDDDDDDDDDDDDDDDDULL);

    /* ── Test 5: swap pairs  imm8 = 0b10_11_00_01 = 0xB1 ─────────── */
    // dst[0]=src[1], dst[1]=src[0], dst[2]=src[3], dst[3]=src[2]
    __m256i r_sp = __builtin_ia32_permdi256(src, 0xB1);
    assert(get64(r_sp, 0) == 0xBBBBBBBBBBBBBBBBULL);
    assert(get64(r_sp, 1) == 0xAAAAAAAAAAAAAAAAULL);
    assert(get64(r_sp, 2) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_sp, 3) == 0xCCCCCCCCCCCCCCCCULL);

    /* ── Test 6: rotate left by 1 lane  imm8 = 0b00_11_10_01 = 0x39 */
    // dst[0]=src[1], dst[1]=src[2], dst[2]=src[3], dst[3]=src[0]
    __m256i r_rot = __builtin_ia32_permdi256(src, 0x39);
    assert(get64(r_rot, 0) == 0xBBBBBBBBBBBBBBBBULL);
    assert(get64(r_rot, 1) == 0xCCCCCCCCCCCCCCCCULL);
    assert(get64(r_rot, 2) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_rot, 3) == 0xAAAAAAAAAAAAAAAAULL);

    /* ── Test 7: duplication  imm8 = 0b11_11_00_00 = 0xFC ─────────── */
    // dst[0]=src[0], dst[1]=src[0], dst[2]=src[3], dst[3]=src[3]
    __m256i r_dup = __builtin_ia32_permdi256(src, 0xFC);
    assert(get64(r_dup, 0) == 0xAAAAAAAAAAAAAAAAULL);    
    assert(get64(r_dup, 1) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_dup, 2) == 0xDDDDDDDDDDDDDDDDULL);
    assert(get64(r_dup, 3) == 0xDDDDDDDDDDDDDDDDULL);

    /* ── Test 8: round-trip — reverse twice is identity ───────────── */
    __m256i r_rt = __builtin_ia32_permdi256(
                       __builtin_ia32_permdi256(src, 0x1B), 0x1B);
    assert(get64(r_rt, 0) == 0xAAAAAAAAAAAAAAAAULL);
    assert(get64(r_rt, 1) == 0xBBBBBBBBBBBBBBBBULL);
    assert(get64(r_rt, 2) == 0xCCCCCCCCCCCCCCCCULL);
    assert(get64(r_rt, 3) == 0xDDDDDDDDDDDDDDDDULL);

    printf("All tests passed.\n");
    return 0;
}

