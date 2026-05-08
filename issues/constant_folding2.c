#include <stdio.h>
#include <stdint.h>
#include <immintrin.h>
#include <string.h>

typedef unsigned __int128 u128;
typedef          __int128 i128;

// --- Global constant expressions: chibicc must evaluate these at init time ---
static const i128 C_ADD    = (__int128)100 + 200;
static const i128 C_MUL    = (__int128)6 * 7;
static const i128 C_SHL32  = (__int128)1 << 32;
static const i128 C_SHL64  = (__int128)1 << 64;
static const i128 C_SHL100 = (__int128)1 << 100;
static const i128 C_CHAIN  = ((__int128)3 * 7 + 1) << 4;
static const i128 C_BIG    = (__int128)0xDEADBEEFULL * 0xCAFEBABEULL;
static const u128 C_OR     = ((u128)0xFFFFFFFFFFFFFFFFULL << 64)
                             | 0xAAAAAAAAAAAAAAAAULL;
static const i128 C_NEG    = -(__int128)42;

int main(void) {
    int pass = 0, fail = 0;

#define CHECK(label, cond) \
    do { if (cond) { pass++; printf("PASS  %s\n", label); } \
         else      { fail++; printf("FAIL  %s\n", label); } } while (0)

#define HI(x) ((uint64_t)((u128)(x) >> 64))
#define LO(x) ((uint64_t)(x))

    /* ------------------------------------------------------------------ */
    printf("=== __int128 : global constant initializers ===\n");
    /* ------------------------------------------------------------------ */

    CHECK("add  : (i128)100 + 200 == 300",
          HI(C_ADD)==0 && LO(C_ADD)==300ULL);

    CHECK("mul  : (i128)6 * 7 == 42",
          HI(C_MUL)==0 && LO(C_MUL)==42ULL);

    CHECK("shl32: (i128)1 << 32  — stays in lo word",
          HI(C_SHL32)==0 && LO(C_SHL32)==0x100000000ULL);

    CHECK("shl64: (i128)1 << 64  — crosses 64-bit word boundary",
          HI(C_SHL64)==1ULL && LO(C_SHL64)==0ULL);

    CHECK("shl100:(i128)1 << 100 — hi=2^36, lo=0",
          HI(C_SHL100)==(1ULL<<36) && LO(C_SHL100)==0ULL);

    CHECK("chain: ((i128)3*7+1)<<4 == 352",
          HI(C_CHAIN)==0 && LO(C_CHAIN)==352ULL);

    CHECK("bigmul:(i128)0xDEADBEEF * 0xCAFEBABE == 0xb092ab7b88cf5b62",
          HI(C_BIG)==0 && LO(C_BIG)==0xb092ab7b88cf5b62ULL);

    CHECK("or128 : hi=0xFFFF...F lo=0xAAAA...A",
          HI(C_OR)==0xFFFFFFFFFFFFFFFFULL && LO(C_OR)==0xAAAAAAAAAAAAAAAAULL);

    CHECK("neg  : -(i128)42",
          HI(C_NEG)==0xFFFFFFFFFFFFFFFFULL && LO(C_NEG)==(uint64_t)(-42LL));

    /* ------------------------------------------------------------------ */
    printf("\n=== __int128 : local constant expressions ===\n");
    /* ------------------------------------------------------------------ */
    {
        i128 loc_big    = (__int128)1000 * 1000 * 1000 * 1000;  // 10^12
        i128 loc_minval = (__int128)1 << 127;                    // INT128_MIN boundary
        i128 loc_div    = (__int128)1000000 / 7;                 // 142857
        i128 loc_mod    = (__int128)1000000 % 7;                 // 1
        i128 loc_and    = (__int128)0xFFFF & 0xAAAA;             // 0xAAAA
        i128 loc_xor    = (__int128)0xFF00FF ^ 0x00FF00;         // 0xFFFFFF
        i128 loc_not    = ~(__int128)0;                          // all bits set
        i128 loc_tern   = (1 ? (__int128)99 : (__int128)-1);    // 99
        i128 loc_sizeof = sizeof(__int128) * 8;                  // 128

        CHECK("local 10^12",
              HI(loc_big)==0 && LO(loc_big)==1000000000000ULL);
        CHECK("local 1<<127  hi=2^63, lo=0",
              HI(loc_minval)==(1ULL<<63) && LO(loc_minval)==0ULL);
        CHECK("local 1000000/7 == 142857",
              HI(loc_div)==0 && LO(loc_div)==142857ULL);
        CHECK("local 1000000%7 == 1",
              HI(loc_mod)==0 && LO(loc_mod)==1ULL);
        CHECK("local 0xFFFF & 0xAAAA == 0xAAAA",
              HI(loc_and)==0 && LO(loc_and)==0xAAAAULL);
        CHECK("local 0xFF00FF ^ 0x00FF00 == 0xFFFFFF",
              HI(loc_xor)==0 && LO(loc_xor)==0xFFFFFFULL);
        CHECK("local ~(i128)0  all bits set",
              HI(loc_not)==0xFFFFFFFFFFFFFFFFULL
           && LO(loc_not)==0xFFFFFFFFFFFFFFFFULL);
        CHECK("local ternary (1?99:-1) == 99",
              HI(loc_tern)==0 && LO(loc_tern)==99ULL);
        CHECK("local sizeof(__int128)*8 == 128",
              HI(loc_sizeof)==0 && LO(loc_sizeof)==128ULL);
    }

#ifdef __AVX2__
    /* ------------------------------------------------------------------ */
    printf("\n=== __m256 / __m256i : constant-expression lane values ===\n");
    /* ------------------------------------------------------------------ */

#define CHECK_LANES_I32(label, vec, expected)                    \
    do {                                                         \
        int32_t _l[8]; memcpy(_l, &(vec), 32);                  \
        int _ok = 1;                                             \
        for (int _i = 0; _i < 8; _i++) _ok &= (_l[_i]==(expected)); \
        CHECK(label, _ok);                                       \
    } while (0)

#define CHECK_LANES_F32(label, vec, expected)                    \
    do {                                                         \
        float _l[8]; memcpy(_l, &(vec), 32);                    \
        int _ok = 1;                                             \
        for (int _i = 0; _i < 8; _i++) _ok &= (_l[_i]==(expected)); \
        CHECK(label, _ok);                                       \
    } while (0)

    // setzero
    {
        __m256i z = _mm256_setzero_si256();
        CHECK_LANES_I32("setzero_si256: all 8 int32 lanes == 0", z, 0);
    }

    // broadcast integer literal
    {
        __m256i v = _mm256_set1_epi32(42);
        CHECK_LANES_I32("set1_epi32(42): all 8 lanes == 42", v, 42);
    }

    // broadcast negative
    {
        __m256i v = _mm256_set1_epi32(-1);
        CHECK_LANES_I32("set1_epi32(-1): all 8 lanes == -1", v, -1);
    }

    // broadcast float literal
    {
        __m256 v = _mm256_set1_ps(1.0f);
        CHECK_LANES_F32("set1_ps(1.0f): all 8 lanes == 1.0f", v, 1.0f);
    }

    // distinct lane literals
    {
        __m256i v = _mm256_set_epi32(7, 6, 5, 4, 3, 2, 1, 0);
        int32_t lanes[8]; memcpy(lanes, &v, 32);
        int ok = 1;
        for (int i = 0; i < 8; i++) ok &= (lanes[i] == i);
        CHECK("set_epi32(7..0): lanes[i] == i", ok);
    }

    // add with literal operands
    {
        __m256i a = _mm256_set1_epi32(10);
        __m256i b = _mm256_set1_epi32(20);
        __m256i c = _mm256_add_epi32(a, b);
        CHECK_LANES_I32("add_epi32(set1(10), set1(20)): all lanes == 30", c, 30);
    }

    // multiply with literal operands
    {
        __m256i a = _mm256_set1_epi32(6);
        __m256i b = _mm256_set1_epi32(7);
        __m256i c = _mm256_mullo_epi32(a, b);
        CHECK_LANES_I32("mullo_epi32(set1(6), set1(7)): all lanes == 42", c, 42);
    }

    // subtract
    {
        __m256i a = _mm256_set1_epi32(100);
        __m256i b = _mm256_set1_epi32(58);
        __m256i c = _mm256_sub_epi32(a, b);
        CHECK_LANES_I32("sub_epi32(set1(100), set1(58)): all lanes == 42", c, 42);
    }

    // bitwise AND
    {
        __m256i a = _mm256_set1_epi32(0xFF);
        __m256i b = _mm256_set1_epi32(0x0F);
        __m256i c = _mm256_and_si256(a, b);
        CHECK_LANES_I32("and_si256(set1(0xFF), set1(0x0F)): all lanes == 15", c, 15);
    }

    // bitwise OR
    {
        __m256i a = _mm256_set1_epi32(0xF0);
        __m256i b = _mm256_set1_epi32(0x0F);
        __m256i c = _mm256_or_si256(a, b);
        CHECK_LANES_I32("or_si256(set1(0xF0), set1(0x0F)): all lanes == 255", c, 255);
    }

    // bitwise XOR
    {
        __m256i a = _mm256_set1_epi32(0xFF);
        __m256i b = _mm256_set1_epi32(0x0F);
        __m256i c = _mm256_xor_si256(a, b);
        CHECK_LANES_I32("xor_si256(set1(0xFF), set1(0x0F)): all lanes == 0xF0==240", c, 0xF0);
    }

    // left shift immediate
    {
        __m256i a = _mm256_set1_epi32(1);
        __m256i c = _mm256_slli_epi32(a, 4);
        CHECK_LANES_I32("slli_epi32(set1(1), 4): all lanes == 16", c, 16);
    }

    // right shift immediate
    {
        __m256i a = _mm256_set1_epi32(256);
        __m256i c = _mm256_srli_epi32(a, 3);
        CHECK_LANES_I32("srli_epi32(set1(256), 3): all lanes == 32", c, 32);
    }

    // compare equal -> all-ones mask
    {
        __m256i a = _mm256_set1_epi32(42);
        __m256i b = _mm256_set1_epi32(42);
        __m256i c = _mm256_cmpeq_epi32(a, b);
        CHECK_LANES_I32("cmpeq_epi32(set1(42),set1(42)): all lanes == -1", c, -1);
    }

    // float add
    {
        __m256 a = _mm256_set1_ps(1.5f);
        __m256 b = _mm256_set1_ps(2.5f);
        __m256 c = _mm256_add_ps(a, b);
        CHECK_LANES_F32("add_ps(set1(1.5f), set1(2.5f)): all lanes == 4.0f", c, 4.0f);
    }

    // float multiply
    {
        __m256 a = _mm256_set1_ps(6.0f);
        __m256 b = _mm256_set1_ps(7.0f);
        __m256 c = _mm256_mul_ps(a, b);
        CHECK_LANES_F32("mul_ps(set1(6.0f), set1(7.0f)): all lanes == 42.0f", c, 42.0f);
    }

    // double broadcast
    {
        __m256d a = _mm256_set1_pd(3.14);
        double lanes[4]; memcpy(lanes, &a, 32);
        int ok = 1;
        for (int i = 0; i < 4; i++) ok &= (lanes[i] == 3.14);
        CHECK("set1_pd(3.14): all 4 double lanes == 3.14", ok);
    }

    // __int128 value split into two 64-bit halves loaded into __m256i
    {
        u128 val = ((u128)0xDEADBEEFULL << 32) | 0xCAFEBABEULL;
        uint64_t lo64 = (uint64_t)val;
        uint64_t hi64 = (uint64_t)(val >> 64);
        __m256i v = _mm256_set_epi64x((int64_t)hi64, (int64_t)lo64,
                                       (int64_t)hi64, (int64_t)lo64);
        uint64_t out[4]; memcpy(out, &v, 32);
        CHECK("__int128 hi/lo -> __m256i epi64 lanes match",
              out[0]==lo64 && out[1]==hi64 && out[2]==lo64 && out[3]==hi64);
    }

#else
    printf("\n=== __m256/__m256i : SKIPPED  (recompile with -mavx2) ===\n");
#endif

    printf("\n=== Results: %d passed, %d failed ===\n", pass, fail);
    return fail > 0 ? 1 : 0;
}
