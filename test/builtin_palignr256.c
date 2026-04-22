// test_avx2_cast2.c
// Tests for __builtin_ia32_si_si256 and _mm256_alignr_epi8
// Compile with: cc -mavx2 -o test_avx2_cast2 test_avx2_cast2.c

#include <immintrin.h>
#include "test.h"
#include <stdint.h>
#include <string.h>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void print_m128i_u8(const char *label, __m128i v) {
    uint8_t buf[16];
    memcpy(buf, &v, 16);
    printf("%s: [", label);
    for (int i = 0; i < 16; i++)
        printf("%3u%s", buf[i], i < 15 ? "," : "]\n");
}

static void print_m256i_u8(const char *label, __m256i v) {
    uint8_t buf[32];
    memcpy(buf, &v, 32);
    printf("%s: [", label);
    for (int i = 0; i < 32; i++)
        printf("%3u%s", buf[i], i < 31 ? "," : "]\n");
}

static void print_m256i_i32(const char *label, __m256i v) {
    int32_t buf[8];
    memcpy(buf, &v, 32);
    printf("%s: [%d, %d, %d, %d, %d, %d, %d, %d]\n",
           label, buf[0], buf[1], buf[2], buf[3],
                  buf[4], buf[5], buf[6], buf[7]);
}

// ---------------------------------------------------------------------------
// Test 1 — __builtin_ia32_si_si256
//   Extracts the LOW 128-bit lane of a __m256i as a __m128i.
//   This is the inverse direction of __builtin_ia32_si256_si:
//     si256_si : __m128i -> __m256i  (promote, zero-extend upper lane)
//     si_si256 : __m256i -> __m128i  (extract low lane)
//   No instruction is emitted; it is a pure compile-time cast.
// ---------------------------------------------------------------------------

static int test_builtin_ia32_si_si256(void) {
    int32_t src[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    __m256i v256 = _mm256_loadu_si256((__m256i *)src);
    print_m256i_i32("  input  (256)", v256);

    __m128i v128 = __builtin_ia32_si_si256(v256);

    int32_t out[4];
    memcpy(out, &v128, 16);
    printf("  output (128): [%d, %d, %d, %d]\n",
           out[0], out[1], out[2], out[3]);

    // Expected: low four int32 lanes {10, 20, 30, 40}
    int ok = (out[0] == 10 && out[1] == 20 && out[2] == 30 && out[3] == 40);
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 2 — _mm256_alignr_epi8  (VPALIGNR ymm)
//   Concatenates pairs of 128-bit lanes from two __m256i operands and
//   right-shifts the concatenated 256-bit value by IMM8 bytes.
//   The operation is performed INDEPENDENTLY on each 128-bit lane pair:
//
//     low  result lane  = (a_low  ++ b_low ) >> (IMM8 * 8)
//     high result lane  = (a_high ++ b_high) >> (IMM8 * 8)
//
//   Test uses IMM8 = 4 (shift right by 4 bytes within each lane pair).
// ---------------------------------------------------------------------------

static int test_mm256_alignr_epi8(void) {
    // Fill 'a' with bytes 0x10..0x1F (low lane) and 0x30..0x3F (high lane)
    // Fill 'b' with bytes 0x20..0x2F (low lane) and 0x40..0x4F (high lane)
    uint8_t a_bytes[32], b_bytes[32];
    for (int i = 0; i < 16; i++) { a_bytes[i]      = 0x10 + i; }
    for (int i = 0; i < 16; i++) { a_bytes[16 + i] = 0x30 + i; }
    for (int i = 0; i < 16; i++) { b_bytes[i]      = 0x20 + i; }
    for (int i = 0; i < 16; i++) { b_bytes[16 + i] = 0x40 + i; }

    __m256i a = _mm256_loadu_si256((__m256i *)a_bytes);
    __m256i b = _mm256_loadu_si256((__m256i *)b_bytes);
    print_m256i_u8("  a      ", a);
    print_m256i_u8("  b      ", b);

    // VPALIGNR: result = concat(a_lane, b_lane) >> (4 bytes)
    // i.e. bytes [4..15] of b_lane followed by bytes [0..11] of a_lane
    __m256i result = _mm256_alignr_epi8(a, b, 4);
    print_m256i_u8("  alignr4", result);

    uint8_t out[32];
    memcpy(out, &result, 32);

    // Build expected output manually for each 128-bit lane
    // Low lane:  concat(a_low=0x10..0x1F, b_low=0x20..0x2F), shift right 4 bytes
    //   => b_low[4..15] ++ a_low[0..11]
    //   => 0x24,0x25,...,0x2F, 0x10,0x11,...,0x1B
    // High lane: concat(a_high=0x30..0x3F, b_high=0x40..0x4F), shift right 4 bytes
    //   => b_high[4..15] ++ a_high[0..11]
    //   => 0x44,0x45,...,0x4F, 0x30,0x31,...,0x3B
    uint8_t expected[32];
    for (int i = 0; i < 12; i++) expected[i]      = 0x24 + i; // b_low  [4..15]
    for (int i = 0; i < 4;  i++) expected[12 + i] = 0x10 + i; // a_low  [0..3]  -- wait, see note
    for (int i = 0; i < 12; i++) expected[16 + i] = 0x44 + i; // b_high [4..15]
    for (int i = 0; i < 4;  i++) expected[28 + i] = 0x30 + i; // a_high [0..3]

    // Note: VPALIGNR(a, b, imm) with Intel notation is:
    //   tmp = a_lane concatenated LEFT of b_lane (a is high part)
    //   result = tmp >> imm*8
    // So concat = [a_low | b_low] (32 bytes), take bytes [4..19]
    //   = a_low[4..15] ++ b_low[0..3]  NO — recheck with Intel manual:
    //
    // Intel: PALIGNR dst, src, imm  =>  tmp[255:0] = dst[127:0]:src[127:0]
    //   (dst is first operand = 'a', src is second = 'b')
    //   result_low  = tmp[127:0]  >> imm*8  (bytes from position imm onward)
    //   i.e. bytes imm..15 of b (src), then bytes 0..(imm-1) of a (dst)
    //
    // With imm=4:
    //   low  result = b_low[4..15]  ++ a_low[0..3]
    //                 0x24..0x2F       0x10..0x13
    //   high result = b_high[4..15] ++ a_high[0..3]
    //                 0x44..0x4F       0x30..0x33
    // (The expected[] array above is already correct — the comment was right.)

    int ok = (memcmp(out, expected, 32) == 0);

    printf("  expected : ");
    for (int i = 0; i < 32; i++)
        printf("%3u%s", expected[i], i < 31 ? "," : "\n");
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 3 — round-trip: si_si256 then si256_si must preserve the low lane
// ---------------------------------------------------------------------------

static int test_roundtrip(void) {
    int32_t src[8] = {-1, 0, 42, 1337, 99, 88, 77, 66};
    __m256i v256   = _mm256_loadu_si256((__m256i *)src);

    // Extract low 128-bit lane via __builtin_ia32_si_si256
    __m128i low    = __builtin_ia32_si_si256(v256);

    // Re-promote to 256 bits via __builtin_ia32_si256_si (zero-extends upper)
    __m256i back   = (__m256i)__builtin_ia32_si256_si(low);

    int32_t out[8];
    memcpy(out, &back, 32);

    // Low lane must match src[0..3]; upper lane must be zero
    int ok = (out[0] == -1 && out[1] == 0  && out[2] == 42 && out[3] == 1337
           && out[4] ==  0 && out[5] == 0  && out[6] ==  0 && out[7] ==    0);
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 4 — _mm256_alignr_epi8 with IMM8 = 0 (identity on b)
// ---------------------------------------------------------------------------

static int test_alignr_imm0(void) {
    uint8_t a_bytes[32], b_bytes[32];
    for (int i = 0; i < 32; i++) { a_bytes[i] = (uint8_t)(0xA0 + i); }
    for (int i = 0; i < 32; i++) { b_bytes[i] = (uint8_t)(0x01 + i); }

    __m256i a = _mm256_loadu_si256((__m256i *)a_bytes);
    __m256i b = _mm256_loadu_si256((__m256i *)b_bytes);

    // IMM8=0 => no shift => result == b (src)
    __m256i result = _mm256_alignr_epi8(a, b, 0);

    uint8_t out[32];
    memcpy(out, &result, 32);

    int ok = (memcmp(out, b_bytes, 32) == 0);
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 5 — _mm256_alignr_epi8 with IMM8 = 16 (identity on a)
// ---------------------------------------------------------------------------

static int test_alignr_imm16(void) {
    uint8_t a_bytes[32], b_bytes[32];
    for (int i = 0; i < 32; i++) { a_bytes[i] = (uint8_t)(0xA0 + i); }
    for (int i = 0; i < 32; i++) { b_bytes[i] = (uint8_t)(0x01 + i); }

    __m256i a = _mm256_loadu_si256((__m256i *)a_bytes);
    __m256i b = _mm256_loadu_si256((__m256i *)b_bytes);

    // IMM8=16 => shift by full lane => result == a (dst)
    __m256i result = _mm256_alignr_epi8(a, b, 16);

    uint8_t out[32];
    memcpy(out, &result, 32);

    int ok = (memcmp(out, a_bytes, 32) == 0);
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(void) {
    int all_pass = 1;

    printf("=== Test 1: __builtin_ia32_si_si256 (extract low 128-bit lane) ===\n");
    all_pass &= test_builtin_ia32_si_si256();

    printf("\n=== Test 2: _mm256_alignr_epi8 (imm=4, standard shift) ===\n");
    all_pass &= test_mm256_alignr_epi8();

    printf("\n=== Test 3: round-trip si_si256 -> si256_si (zero-extend) ===\n");
    all_pass &= test_roundtrip();

    printf("\n=== Test 4: _mm256_alignr_epi8 (imm=0, identity on b/src) ===\n");
    all_pass &= test_alignr_imm0();

    printf("\n=== Test 5: _mm256_alignr_epi8 (imm=16, identity on a/dst) ===\n");
    all_pass &= test_alignr_imm16();

    printf("\n=== Overall: %s ===\n", all_pass ? "ALL PASS" : "SOME FAILURES");
    return all_pass ? 0 : 1;
}
