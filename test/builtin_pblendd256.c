// test_avx2_blend_epi32.c
// Tests for _mm256_blend_epi32
// Compile with: cc -mavx2 -o test_avx2_blend_epi32 test_avx2_blend_epi32.c

#include <immintrin.h>
#include "test.h"
#include <stdint.h>
#include <string.h>

// ---------------------------------------------------------------------------
// The instruction: VPBLENDD ymm, ymm, ymm/m256, imm8
//
// _mm256_blend_epi32(a, b, imm8)
//
// Selects 32-bit integer lanes from 'a' or 'b' according to each bit of imm8:
//   bit i = 0  =>  result lane i = a lane i
//   bit i = 1  =>  result lane i = b lane i
//
// 8 bits control 8 int32 lanes (the full 256-bit register).
//
// Common patterns:
//   0x00  all from a
//   0xFF  all from b
//   0xF0  low 4 from a, high 4 from b
//   0x0F  low 4 from b, high 4 from a
//   0xAA  alternating b,a,b,a,b,a,b,a  (bits: 10101010)
//   0x55  alternating a,b,a,b,a,b,a,b  (bits: 01010101)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void print_m256i_i32(const char *label, __m256i v) {
    int32_t buf[8];
    memcpy(buf, &v, 32);
    printf("  %-24s [%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d]\n", label,
           buf[0], buf[1], buf[2], buf[3],
           buf[4], buf[5], buf[6], buf[7]);
}

static int cmp256_i32(const __m256i result, const int32_t expected[8]) {
    int32_t out[8];
    memcpy(out, &result, 32);
    if (memcmp(out, expected, 32) == 0) return 1;
    // On failure print which lanes differ
    printf("  MISMATCH:\n");
    printf("    got     : [%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d]\n",
           out[0], out[1], out[2], out[3],
           out[4], out[5], out[6], out[7]);
    printf("    expected: [%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d]\n",
           expected[0], expected[1], expected[2], expected[3],
           expected[4], expected[5], expected[6], expected[7]);
    return 0;
}

// ---------------------------------------------------------------------------
// Fixtures
//   a : { 1, 2, 3, 4, 5, 6, 7, 8 }
//   b : {11,22,33,44,55,66,77,88 }
// ---------------------------------------------------------------------------

static __m256i make_a(void) {
    int32_t s[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return _mm256_loadu_si256((__m256i *)s);
}
static __m256i make_b(void) {
    int32_t s[8] = {11, 22, 33, 44, 55, 66, 77, 88};
    return _mm256_loadu_si256((__m256i *)s);
}

// ---------------------------------------------------------------------------
// Test 1 — imm8 = 0x00  (all lanes from a)
//   every bit = 0  =>  result = a
// ---------------------------------------------------------------------------
static int test_imm_0x00(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0x00);
    print_m256i_i32("result (0x00)", r);
    int32_t expected[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 2 — imm8 = 0xFF  (all lanes from b)
//   every bit = 1  =>  result = b
// ---------------------------------------------------------------------------
static int test_imm_0xFF(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0xFF);
    print_m256i_i32("result (0xFF)", r);
    int32_t expected[8] = {11, 22, 33, 44, 55, 66, 77, 88};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 3 — imm8 = 0xF0  (low 4 lanes from a, high 4 lanes from b)
//   bits[3:0]=0b0000  =>  lanes 0-3 from a = {1,2,3,4}
//   bits[7:4]=0b1111  =>  lanes 4-7 from b = {55,66,77,88}
// ---------------------------------------------------------------------------
static int test_imm_0xF0(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0xF0);
    print_m256i_i32("result (0xF0)", r);
    int32_t expected[8] = {1, 2, 3, 4, 55, 66, 77, 88};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 4 — imm8 = 0x0F  (low 4 lanes from b, high 4 lanes from a)
//   bits[3:0]=0b1111  =>  lanes 0-3 from b = {11,22,33,44}
//   bits[7:4]=0b0000  =>  lanes 4-7 from a = {5,6,7,8}
// ---------------------------------------------------------------------------
static int test_imm_0x0F(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0x0F);
    print_m256i_i32("result (0x0F)", r);
    int32_t expected[8] = {11, 22, 33, 44, 5, 6, 7, 8};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 5 — imm8 = 0xAA  (alternating b,a,b,a,b,a,b,a)
//   0xAA = 0b10101010
//   bit 0=0 => lane 0 from a =  1
//   bit 1=1 => lane 1 from b = 22
//   bit 2=0 => lane 2 from a =  3
//   bit 3=1 => lane 3 from b = 44
//   bit 4=0 => lane 4 from a =  5
//   bit 5=1 => lane 5 from b = 66
//   bit 6=0 => lane 6 from a =  7
//   bit 7=1 => lane 7 from b = 88
// ---------------------------------------------------------------------------
static int test_imm_0xAA(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0xAA);
    print_m256i_i32("result (0xAA)", r);
    int32_t expected[8] = {1, 22, 3, 44, 5, 66, 7, 88};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 6 — imm8 = 0x55  (alternating a,b,a,b,a,b,a,b)
//   0x55 = 0b01010101
//   bit 0=1 => lane 0 from b = 11
//   bit 1=0 => lane 1 from a =  2
//   bit 2=1 => lane 2 from b = 33
//   bit 3=0 => lane 3 from a =  4
//   bit 4=1 => lane 4 from b = 55
//   bit 5=0 => lane 5 from a =  6
//   bit 6=1 => lane 6 from b = 77
//   bit 7=0 => lane 7 from a =  8
// ---------------------------------------------------------------------------
static int test_imm_0x55(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0x55);
    print_m256i_i32("result (0x55)", r);
    int32_t expected[8] = {11, 2, 33, 4, 55, 6, 77, 8};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 7 — imm8 = 0x01  (single lane: only lane 0 from b)
//   0x01 = 0b00000001
//   bit 0=1 => lane 0 from b = 11
//   all others from a
// ---------------------------------------------------------------------------
static int test_imm_0x01(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0x01);
    print_m256i_i32("result (0x01)", r);
    int32_t expected[8] = {11, 2, 3, 4, 5, 6, 7, 8};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 8 — imm8 = 0x80  (single lane: only lane 7 from b)
//   0x80 = 0b10000000
//   bit 7=1 => lane 7 from b = 88
//   all others from a
// ---------------------------------------------------------------------------
static int test_imm_0x80(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0x80);
    print_m256i_i32("result (0x80)", r);
    int32_t expected[8] = {1, 2, 3, 4, 5, 6, 7, 88};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 9 — imm8 = 0x66  (inner 4 lanes from b, outer 2+2 from a)
//   0x66 = 0b01100110
//   bit 0=0 => lane 0 from a =  1
//   bit 1=1 => lane 1 from b = 22
//   bit 2=1 => lane 2 from b = 33
//   bit 3=0 => lane 3 from a =  4
//   bit 4=0 => lane 4 from a =  5
//   bit 5=1 => lane 5 from b = 66
//   bit 6=1 => lane 6 from b = 77
//   bit 7=0 => lane 7 from a =  8
// ---------------------------------------------------------------------------
static int test_imm_0x66(void) {
    __m256i a = make_a(), b = make_b();
    __m256i r = _mm256_blend_epi32(a, b, 0x66);
    print_m256i_i32("result (0x66)", r);
    int32_t expected[8] = {1, 22, 33, 4, 5, 66, 77, 8};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 10 — negative values: verify blending works correctly with sign bits
// ---------------------------------------------------------------------------
static int test_negative_values(void) {
    int32_t sa[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    int32_t sb[8] = {-11, -22, -33, -44, -55, -66, -77, -88};
    __m256i a = _mm256_loadu_si256((__m256i *)sa);
    __m256i b = _mm256_loadu_si256((__m256i *)sb);
    print_m256i_i32("a (negative)", a);
    print_m256i_i32("b (negative)", b);

    // 0xCC = 0b11001100
    // lanes 2,3,6,7 from b; lanes 0,1,4,5 from a
    __m256i r = _mm256_blend_epi32(a, b, 0xCC);
    print_m256i_i32("result (0xCC)", r);
    int32_t expected[8] = {-1, -2, -33, -44, -5, -6, -77, -88};
    int ok = cmp256_i32(r, expected);
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(void) {
    int all_pass = 1;

    printf("Fixtures:\n");
    print_m256i_i32("a", make_a());
    print_m256i_i32("b", make_b());
    printf("\n");

    printf("=== Test  1: imm8=0x00  all from a                      ===\n");
    all_pass &= test_imm_0x00();

    printf("=== Test  2: imm8=0xFF  all from b                      ===\n");
    all_pass &= test_imm_0xFF();

    printf("=== Test  3: imm8=0xF0  low4=a, high4=b                 ===\n");
    all_pass &= test_imm_0xF0();

    printf("=== Test  4: imm8=0x0F  low4=b, high4=a                 ===\n");
    all_pass &= test_imm_0x0F();

    printf("=== Test  5: imm8=0xAA  alternating a,b (even=a,odd=b)  ===\n");
    all_pass &= test_imm_0xAA();

    printf("=== Test  6: imm8=0x55  alternating b,a (even=b,odd=a)  ===\n");
    all_pass &= test_imm_0x55();

    printf("=== Test  7: imm8=0x01  single lane 0 from b            ===\n");
    all_pass &= test_imm_0x01();

    printf("=== Test  8: imm8=0x80  single lane 7 from b            ===\n");
    all_pass &= test_imm_0x80();

    printf("=== Test  9: imm8=0x66  inner pairs from b              ===\n");
    all_pass &= test_imm_0x66();

    printf("=== Test 10: imm8=0xCC  negative values                 ===\n");
    all_pass &= test_negative_values();

    printf("=== Overall: %s ===\n", all_pass ? "ALL PASS" : "SOME FAILURES");
    return all_pass ? 0 : 1;
}
