// test_avx2_permute2x128.c
// Tests for _mm256_permute2x128_si256
// Compile with: cc -mavx2 -o test_avx2_permute2x128 test_avx2_permute2x128.c

#include <immintrin.h>
#include "test.h"
#include <stdint.h>
#include <string.h>

// ---------------------------------------------------------------------------
// The instruction: VPERM2I128 ymm, ymm, ymm, imm8
//
// _mm256_permute2x128_si256(a, b, imm8)
//
// The imm8 byte controls which 128-bit lane goes into each half of the result:
//
//   bits [1:0]  select the SOURCE for the LOW  output lane:
//     0b00 = a_low    0b01 = a_high
//     0b10 = b_low    0b11 = b_high
//   bit  [3]    if set, zero the LOW  output lane
//
//   bits [5:4]  select the SOURCE for the HIGH output lane:
//     0b00 = a_low    0b01 = a_high
//     0b10 = b_low    0b11 = b_high
//   bit  [7]    if set, zero the HIGH output lane
//
// Encoding summary (common imm8 values):
//   0x00  low=a_low,  high=a_low    (broadcast a_low)
//   0x01  low=a_high, high=a_low
//   0x02  low=b_low,  high=a_low
//   0x03  low=b_high, high=a_low
//   0x20  low=a_low,  high=b_low
//   0x31  low=a_high, high=b_high   (swap lanes of a)
//   0x20  low=a_low,  high=b_low
//   0x30  low=a_low,  high=b_low    -- same as 0x20? no: bits[5:4]=0b11=b_high
//   0x31  low=a_high, high=b_high
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void print_m256i_i32(const char *label, __m256i v) {
    int32_t buf[8];
    memcpy(buf, &v, 32);
    printf("  %-22s [%4d,%4d,%4d,%4d | %4d,%4d,%4d,%4d]\n", label,
           buf[0], buf[1], buf[2], buf[3],
           buf[4], buf[5], buf[6], buf[7]);
}

static int cmp256(const __m256i result, const int32_t expected[8]) {
    int32_t out[8];
    memcpy(out, &result, 32);
    return memcmp(out, expected, 32) == 0;
}

// ---------------------------------------------------------------------------
// Fixtures
//   a : low lane = { 1, 2, 3, 4 }   high lane = { 5, 6, 7, 8 }
//   b : low lane = { 9,10,11,12 }   high lane = {13,14,15,16}
// ---------------------------------------------------------------------------

static __m256i make_a(void) {
    int32_t s[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return _mm256_loadu_si256((__m256i *)s);
}
static __m256i make_b(void) {
    int32_t s[8] = {9, 10, 11, 12, 13, 14, 15, 16};
    return _mm256_loadu_si256((__m256i *)s);
}

// ---------------------------------------------------------------------------
// Test 1 — imm8 = 0x20
//   bits[1:0]=0b00 => low  output = a_low  = {1,2,3,4}
//   bits[5:4]=0b10 => high output = b_low  = {9,10,11,12}
// ---------------------------------------------------------------------------
static int test_imm_0x20(void) {
    __m256i a = make_a(), b = make_b();
    print_m256i_i32("a", a);
    print_m256i_i32("b", b);

    __m256i r = _mm256_permute2x128_si256(a, b, 0x20);
    print_m256i_i32("result (0x20)", r);

    int32_t expected[8] = {1, 2, 3, 4, 9, 10, 11, 12};
    int ok = cmp256(r, expected);
    printf("  expected          [   1,   2,   3,   4 |    9,  10,  11,  12]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 2 — imm8 = 0x31
//   bits[1:0]=0b01 => low  output = a_high = {5,6,7,8}
//   bits[5:4]=0b11 => high output = b_high = {13,14,15,16}
// ---------------------------------------------------------------------------
static int test_imm_0x31(void) {
    __m256i a = make_a(), b = make_b();

    __m256i r = _mm256_permute2x128_si256(a, b, 0x31);
    print_m256i_i32("result (0x31)", r);

    int32_t expected[8] = {5, 6, 7, 8, 13, 14, 15, 16};
    int ok = cmp256(r, expected);
    printf("  expected          [   5,   6,   7,   8 |   13,  14,  15,  16]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 3 — imm8 = 0x00  (broadcast a_low into both lanes)
//   bits[1:0]=0b00 => low  output = a_low = {1,2,3,4}
//   bits[5:4]=0b00 => high output = a_low = {1,2,3,4}
// ---------------------------------------------------------------------------
static int test_imm_0x00(void) {
    __m256i a = make_a(), b = make_b();

    __m256i r = _mm256_permute2x128_si256(a, b, 0x00);
    print_m256i_i32("result (0x00)", r);

    int32_t expected[8] = {1, 2, 3, 4, 1, 2, 3, 4};
    int ok = cmp256(r, expected);
    printf("  expected          [   1,   2,   3,   4 |    1,   2,   3,   4]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 4 — imm8 = 0x11  (broadcast a_high into both lanes)
//   bits[1:0]=0b01 => low  output = a_high = {5,6,7,8}
//   bits[5:4]=0b01 => high output = a_high = {5,6,7,8}
// ---------------------------------------------------------------------------
static int test_imm_0x11(void) {
    __m256i a = make_a(), b = make_b();

    __m256i r = _mm256_permute2x128_si256(a, b, 0x11);
    print_m256i_i32("result (0x11)", r);

    int32_t expected[8] = {5, 6, 7, 8, 5, 6, 7, 8};
    int ok = cmp256(r, expected);
    printf("  expected          [   5,   6,   7,   8 |    5,   6,   7,   8]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 5 — imm8 = 0x03  (b_high into low lane, a_low into high lane)
//   bits[1:0]=0b11 => low  output = b_high = {13,14,15,16}
//   bits[5:4]=0b00 => high output = a_low  = {1,2,3,4}
// ---------------------------------------------------------------------------
static int test_imm_0x03(void) {
    __m256i a = make_a(), b = make_b();

    __m256i r = _mm256_permute2x128_si256(a, b, 0x03);
    print_m256i_i32("result (0x03)", r);

    int32_t expected[8] = {13, 14, 15, 16, 1, 2, 3, 4};
    int ok = cmp256(r, expected);
    printf("  expected          [  13,  14,  15,  16 |    1,   2,   3,   4]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 6 — imm8 = 0x08  (zero low lane, a_low into high lane)
//   bit [3]=1      => low  output = zeroed       = {0,0,0,0}
//   bits[5:4]=0b00 => high output = a_low        = {1,2,3,4}
// ---------------------------------------------------------------------------
static int test_imm_0x08(void) {
    __m256i a = make_a(), b = make_b();

    __m256i r = _mm256_permute2x128_si256(a, b, 0x08);
    print_m256i_i32("result (0x08)", r);

    int32_t expected[8] = {0, 0, 0, 0, 1, 2, 3, 4};
    int ok = cmp256(r, expected);
    printf("  expected          [   0,   0,   0,   0 |    1,   2,   3,   4]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 7 — imm8 = 0x80  (a_low into low lane, zero high lane)
//   bits[1:0]=0b00 => low  output = a_low  = {1,2,3,4}
//   bit [7]=1      => high output = zeroed = {0,0,0,0}
// ---------------------------------------------------------------------------
static int test_imm_0x80(void) {
    __m256i a = make_a(), b = make_b();

    __m256i r = _mm256_permute2x128_si256(a, b, 0x80);
    print_m256i_i32("result (0x80)", r);

    int32_t expected[8] = {1, 2, 3, 4, 0, 0, 0, 0};
    int ok = cmp256(r, expected);
    printf("  expected          [   1,   2,   3,   4 |    0,   0,   0,   0]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 8 — imm8 = 0x88  (zero both lanes)
//   bit [3]=1 => low  output = zeroed
//   bit [7]=1 => high output = zeroed
// ---------------------------------------------------------------------------
static int test_imm_0x88(void) {
    __m256i a = make_a(), b = make_b();

    __m256i r = _mm256_permute2x128_si256(a, b, 0x88);
    print_m256i_i32("result (0x88)", r);

    int32_t expected[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int ok = cmp256(r, expected);
    printf("  expected          [   0,   0,   0,   0 |    0,   0,   0,   0]\n");
    printf("  result: %s\n\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(void) {
    int all_pass = 1;
    __m256i a = make_a(), b = make_b();
    printf("Fixtures:\n");
    print_m256i_i32("a (low|high)", a);
    print_m256i_i32("b (low|high)", b);
    printf("\n");

    printf("=== Test 1: imm8=0x20  low=a_low,  high=b_low  ===\n");
    all_pass &= test_imm_0x20();

    printf("=== Test 2: imm8=0x31  low=a_high, high=b_high ===\n");
    all_pass &= test_imm_0x31();

    printf("=== Test 3: imm8=0x00  broadcast a_low         ===\n");
    all_pass &= test_imm_0x00();

    printf("=== Test 4: imm8=0x11  broadcast a_high        ===\n");
    all_pass &= test_imm_0x11();

    printf("=== Test 5: imm8=0x03  low=b_high, high=a_low  ===\n");
    all_pass &= test_imm_0x03();

    printf("=== Test 6: imm8=0x08  low=zero,   high=a_low  ===\n");
    all_pass &= test_imm_0x08();

    printf("=== Test 7: imm8=0x80  low=a_low,  high=zero   ===\n");
    all_pass &= test_imm_0x80();

    printf("=== Test 8: imm8=0x88  zero both lanes         ===\n");
    all_pass &= test_imm_0x88();

    printf("=== Overall: %s ===\n", all_pass ? "ALL PASS" : "SOME FAILURES");
    return all_pass ? 0 : 1;
}
