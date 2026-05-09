// test_avx2_cast.c
// Tests for _mm256_castsi256_si128 and __builtin_ia32_si256_si
// Compile with: cc -mavx2 -o test_avx2_cast test_avx2_cast.c

#include <immintrin.h>
#include "test.h"
#include <stdint.h>
#include <string.h>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static void print_m128i(const char *label, __m128i v) {
    int32_t buf[4];
    memcpy(buf, &v, 16);
    printf("%s: [%d, %d, %d, %d]\n", label, buf[0], buf[1], buf[2], buf[3]);
}

static void print_m256i(const char *label, __m256i v) {
    int32_t buf[8];
    memcpy(buf, &v, 32);
    printf("%s: [%d, %d, %d, %d, %d, %d, %d, %d]\n",
           label, buf[0], buf[1], buf[2], buf[3],
                  buf[4], buf[5], buf[6], buf[7]);
}

// ---------------------------------------------------------------------------
// Test 1 — _mm256_castsi256_si128
//   Extracts the low 128-bit lane of a 256-bit integer vector.
//   The upper 128 bits are discarded (no data movement occurs).
// ---------------------------------------------------------------------------

static int test_mm256_castsi256_si128(void) {
    int32_t src[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    __m256i v256 = _mm256_loadu_si256((__m256i *)src);
    print_m256i("  input (256)", v256);

    __m128i v128 = _mm256_castsi256_si128(v256);
    print_m128i("  low 128    ", v128);

    // Expected: the low four int32 lanes {1, 2, 3, 4}
    int32_t out[4];
    memcpy(out, &v128, 16);
    int ok = (out[0] == 1 && out[1] == 2 && out[2] == 3 && out[3] == 4);
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 2 — __builtin_ia32_si256_si
//   GCC/clang builtin: zero-extends a __m128i to __m256i
//   (upper 128 bits are zeroed).  This is the low-level form of
//   _mm256_zextsi128_si256 / _mm256_castsi128_si256 depending on the target.
// ---------------------------------------------------------------------------

static int test_builtin_ia32_si256_si(void) {
    int32_t src[4] = {10, 20, 30, 40};
    __m128i v128 = _mm_loadu_si128((__m128i *)src);
    print_m128i("  input (128)", v128);

    // __builtin_ia32_si256_si promotes __m128i -> __m256i
    __m256i v256 = (__m256i)__builtin_ia32_si256_si((__v4si)v128);
    print_m256i("  result(256)", v256);

    // Expected: low four lanes == src, upper four lanes == 0
    int32_t out[8];
    memcpy(out, &v256, 32);
    int ok = (out[0] == 10 && out[1] == 20 && out[2] == 30 && out[3] == 40
           && out[4] ==  0 && out[5] ==  0 && out[6] ==  0 && out[7] ==  0);
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// Test 3 — round-trip: si256_si then castsi256_si128 must give back original
// ---------------------------------------------------------------------------

static int test_roundtrip(void) {
    int32_t src[4] = {-1, 0, 42, 1337};
    __m128i original = _mm_loadu_si128((__m128i *)src);

    __m256i promoted = (__m256i)__builtin_ia32_si256_si((__v4si)original);
    __m128i recovered = (__m128i)_mm256_castsi256_si128(promoted);

    int32_t out[4];
    memcpy(out, &recovered, 16);
    int ok = (out[0] == src[0] && out[1] == src[1]
           && out[2] == src[2] && out[3] == src[3]);
    printf("  result: %s\n", ok ? "PASS" : "FAIL");
    return ok;
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(void) {
    int all_pass = 1;

    printf("=== Test 1: _mm256_castsi256_si128 ===\n");
    all_pass &= test_mm256_castsi256_si128();

    printf("\n=== Test 2: __builtin_ia32_si256_si ===\n");
    all_pass &= test_builtin_ia32_si256_si();

    printf("\n=== Test 3: round-trip (si256_si -> castsi256_si128) ===\n");
    all_pass &= test_roundtrip();

    printf("\n=== Overall: %s ===\n", all_pass ? "ALL PASS" : "SOME FAILURES");
    return all_pass ? 0 : 1;
}