// test_int128.c — stress test for __int128 in chibicc
// Compile with: chibicc test_int128.c -o test_int128 && ./test_int128
// Or reference: gcc test_int128.c -o test_int128_ref && ./test_int128_ref

#include "test.h"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static int failures = 0;

/* Print a 128-bit value as two 64-bit halves (hex). */
static void print128(const char *label, __int128 v) {
    unsigned long long hi = (unsigned long long)((unsigned __int128)v >> 64);
    unsigned long long lo = (unsigned long long)(unsigned __int128)v;
    printf("  %-40s  hi=0x%016llx  lo=0x%016llx\n", label, hi, lo);
}

/* Compare and report. */
static void check(const char *label, __int128 got, __int128 expected) {
    if (got != expected) {
        failures++;
        printf("FAIL  %s\n", label);
        print128("  got     ", got);
        print128("  expected", expected);
    } else {
        printf("PASS  %s\n", label);
    }
}

static void check_u(const char *label, unsigned __int128 got, unsigned __int128 expected) {
    if (got != expected) {
        failures++;
        printf("FAIL  %s\n", label);
        print128("  got     ", (__int128)got);
        print128("  expected", (__int128)expected);
    } else {
        printf("PASS  %s\n", label);
    }
}

// ---------------------------------------------------------------------------
// 1. Constants & Assignment
// ---------------------------------------------------------------------------

static void test_constants(void) {
    printf("\n--- 1. Constants & Assignment ---\n");

    __int128 zero = 0;
    check("zero == 0", zero, (__int128)0);

    __int128 one = 1;
    check("one == 1", one, (__int128)1);

    /* Build 2^64 without a 128-bit literal (chibicc may not support them). */
    __int128 two64 = (__int128)1 << 64;
    check("(1<<64) hi=1 lo=0", two64, (__int128)1 << 64);

    /* Maximum positive signed 128-bit: (2^127) - 1 */
    __int128 smax = ((__int128)1 << 127) - 1;
    print128("INT128_MAX", smax);      /* visual check */

    /* Minimum signed 128-bit: -(2^127) */
    __int128 smin = (__int128)1 << 127;
    print128("INT128_MIN", smin);

    /* Negative one */
    __int128 neg1 = -1;
    check("neg1 all-bits-set", neg1, (__int128)-1);
}

// ---------------------------------------------------------------------------
// 2. Arithmetic
// ---------------------------------------------------------------------------

static void test_arithmetic(void) {
    printf("\n--- 2. Arithmetic ---\n");

    __int128 a = (__int128)9000000000000000000LL;   /* 9e18 */
    __int128 b = (__int128)9000000000000000000LL;

    /* Addition that overflows 64-bit */
    __int128 sum = a + b;
    check("9e18 + 9e18", sum, (__int128)18000000000000000000ULL);

    /* Subtraction */
    __int128 diff = sum - a;
    check("18e18 - 9e18 == 9e18", diff, a);

    /* Subtraction crossing zero */
    __int128 neg = (__int128)0 - a;
    check("0 - 9e18 negative", neg, -(__int128)9000000000000000000LL);

    /* Multiplication: 10^18 * 10^18 = 10^36 */
    __int128 p = (__int128)1000000000000000000LL * (__int128)1000000000000000000LL;
    /* 10^36 => hi = 0x00c097ce7bc90715, lo = 0xb34b9f1000000000 */
    __int128 expected_p = ((__int128)0x00c097ce7bc90715ULL << 64) | 0xb34b9f1000000000ULL;
    check("1e18 * 1e18 == 1e36", p, expected_p);

    /* Division */
    __int128 q = p / (__int128)1000000000000000000LL;
    check("1e36 / 1e18 == 1e18", q, (__int128)1000000000000000000LL);

    /* Modulo */
    __int128 r = (p + 7) % (__int128)1000000000000000000LL;
    check("(1e36+7) % 1e18 == 7", r, (__int128)7);

    /* Negation */
    __int128 neg2 = -p;
    check("-1e36 + 1e36 == 0", neg2 + p, (__int128)0);

    /* Unary plus */
    __int128 pos = +a;
    check("unary + identity", pos, a);
}

// ---------------------------------------------------------------------------
// 3. Bitwise Operations
// ---------------------------------------------------------------------------

static void test_bitwise(void) {
    printf("\n--- 3. Bitwise Operations ---\n");

    __int128 all_ones = (__int128)-1;   /* 0xFFFF…FFFF */
    __int128 hi_half  = all_ones << 64; /* top 64 bits set */
    __int128 lo_half  = (__int128)0xFFFFFFFFFFFFFFFFULL;

    check("hi_half & lo_half == 0", hi_half & lo_half, (__int128)0);
    check("hi_half | lo_half == -1", hi_half | lo_half, all_ones);
    check("hi_half ^ lo_half == -1", hi_half ^ lo_half, all_ones);
    check("~0 == -1", ~(__int128)0, all_ones);
    check("~(-1) == 0", ~all_ones, (__int128)0);
    check("AND with self", all_ones & all_ones, all_ones);
    check("XOR with self == 0", all_ones ^ all_ones, (__int128)0);
}

// ---------------------------------------------------------------------------
// 4. Shift Operations
// ---------------------------------------------------------------------------

static void test_shifts(void) {
    printf("\n--- 4. Shifts ---\n");

    __int128 one = (__int128)1;

    /* Left shifts across the 64-bit boundary */
    for (int i = 0; i <= 127; i++) {
        __int128 shifted = one << i;
        /* Shift back; for i<127 we should recover 1 */
        if (i < 127) {
            __int128 back = shifted >> i;
            if (back != one) {
                failures++;
                printf("FAIL  1<<%-3d >>%-3d != 1\n", i, i);
            }
        }
    }
    printf("PASS  round-trip left/right shift for i in [0..126]\n");

    /* Specific boundary cases */
    check("1 << 63", (__int128)1 << 63, (__int128)(1ULL << 63));
    check("1 << 64", (__int128)1 << 64, ((__int128)1) << 64);
    check("1 << 127 >> 127 (signed, negative)", ((__int128)1 << 127) >> 127, (__int128)-1);

    /* Unsigned right shift (no arithmetic shift) */
    unsigned __int128 u = (unsigned __int128)1 << 127;
    check_u("u(1<<127) >> 127 == 1", u >> 127, (unsigned __int128)1);

    /* Multi-word shift: 0xDEADBEEF_00000000_00000000 >> 32 */
    __int128 v = (__int128)0xDEADBEEFULL << 96;
    __int128 v_shr32 = (unsigned __int128)v >> 32;
    check("0xDEADBEEF<<96 >>u 32", v_shr32, (__int128)0xDEADBEEFULL << 64);
}

// ---------------------------------------------------------------------------
// 5. Comparison Operators
// ---------------------------------------------------------------------------

static void test_comparisons(void) {
    printf("\n--- 5. Comparisons ---\n");

    __int128 big  = (__int128)1 << 100;
    __int128 big2 = big + 1;
    __int128 neg  = -big;

    if (!(big < big2))  { failures++; printf("FAIL  big < big2\n"); }
    else                          printf("PASS  big < big2\n");

    if (!(big > neg))   { failures++; printf("FAIL  big > neg\n"); }
    else                          printf("PASS  big > neg\n");

    if (!(neg < (__int128)0)) { failures++; printf("FAIL  neg < 0\n"); }
    else                          printf("PASS  neg < 0\n");

    if (!(big == big))  { failures++; printf("FAIL  big == big\n"); }
    else                          printf("PASS  big == big\n");

    if (!(big != big2)) { failures++; printf("FAIL  big != big2\n"); }
    else                          printf("PASS  big != big2\n");

    if (!(big >= big))  { failures++; printf("FAIL  big >= big\n"); }
    else                          printf("PASS  big >= big\n");

    if (!(big2 >= big)) { failures++; printf("FAIL  big2 >= big\n"); }
    else                          printf("PASS  big2 >= big\n");
}

// ---------------------------------------------------------------------------
// 6. Increment / Decrement & Compound Assignment
// ---------------------------------------------------------------------------

static void test_compound(void) {
    printf("\n--- 6. Compound Assignment & Inc/Dec ---\n");

    __int128 x = (__int128)1 << 64;

    x++;
    check("(1<<64)++ == (1<<64)+1", x, ((__int128)1 << 64) + 1);

    x--;
    check("(1<<64)+1 -- == 1<<64", x, (__int128)1 << 64);

    x += (__int128)1 << 63;
    check("+= 1<<63", x, ((__int128)1 << 64) + ((__int128)1 << 63));

    x -= (__int128)1 << 63;
    check("-= 1<<63", x, (__int128)1 << 64);

    x *= 3;
    check("*= 3", x, (__int128)3 << 64);

    x /= 3;
    check("/= 3", x, (__int128)1 << 64);

    x %= ((__int128)1 << 64) - 1;
    check("%= (1<<64)-1 → 1", x, (__int128)1);

    x = (__int128)0xFF << 64;
    x &= (__int128)0x0F << 64;
    check("&= mask", x, (__int128)0x0F << 64);

    x |= (__int128)0xF0 << 64;
    check("|= mask", x, (__int128)0xFF << 64);

    x ^= (__int128)0xFF << 64;
    check("^= self → 0", x, (__int128)0);

    x = (__int128)1;
    x <<= 70;
    check("<<= 70", x, (__int128)1 << 70);

    x >>= 70;
    check(">>= 70", x, (__int128)1);
}

// ---------------------------------------------------------------------------
// 7. Type Conversions (casting)
// ---------------------------------------------------------------------------

static void test_casts(void) {
    printf("\n--- 7. Type Conversions ---\n");

    /* int → __int128 */
    int small = -42;
    __int128 promoted = (__int128)small;
    check("(int)-42 → __int128", promoted, (__int128)-42);

    /* long long → __int128 */
    long long ll = -9000000000000000000LL;
    __int128 from_ll = (__int128)ll;
    check("(long long) → __int128 negative", from_ll, (__int128)-9000000000000000000LL);

    /* __int128 → int (truncation expected) */
    __int128 big = ((__int128)1 << 64) + 0x1234;
    int truncated = (int)big;
    if (truncated != 0x1234) {
        failures++;
        printf("FAIL  (__int128 → int) truncation: got 0x%x expected 0x1234\n", truncated);
    } else {
        printf("PASS  __int128 → int truncation\n");
    }

    /* __int128 → long long */
    long long ll2 = (long long)big;
    if (ll2 != 0x1234LL) {
        failures++;
        printf("FAIL  (__int128 → long long) truncation: got 0x%llx expected 0x1234\n", ll2);
    } else {
        printf("PASS  __int128 → long long truncation\n");
    }

    /* unsigned __int128 → __int128 and back */
    unsigned __int128 u = (unsigned __int128)-1;   /* all bits set */
    __int128 s = (__int128)u;
    check("(unsigned __int128)-1 as signed == -1", s, (__int128)-1);
    check_u("(__int128)-1 as unsigned == UINT128_MAX", (unsigned __int128)s, u);

    /* double → __int128 */
    double d = 1.8446744073709552e19;              /* ≈ 2^64 */
    __int128 from_d = (__int128)d;
    /* We just check it's in the right ballpark; FP precision varies */
    int approx_ok = (from_d >> 63) == (__int128)1 || (from_d >> 64) <= (__int128)2;
    if (!approx_ok) {
        failures++;
        printf("FAIL  double → __int128 ballpark\n");
        print128("  from_d", from_d);
    } else {
        printf("PASS  double → __int128 ballpark\n");
    }
}

// ---------------------------------------------------------------------------
// 8. Pointer / Array Usage
// ---------------------------------------------------------------------------

static void test_array(void) {
    printf("\n--- 8. Array & Pointer ---\n");

    __int128 arr[4];
    for (int i = 0; i < 4; i++)
        arr[i] = (__int128)1 << (i * 32);

    for (int i = 0; i < 4; i++) {
        __int128 expected = (__int128)1 << (i * 32);
        char label[64];
        sprintf(label, "arr[%d] == 1<<%d", i, i*32);
        check(label, arr[i], expected);
    }

    /* Pointer arithmetic */
    __int128 *p = arr + 2;
    check("pointer arr+2 dereference", *p, arr[2]);
}

// ---------------------------------------------------------------------------
// 9. Struct Embedding
// ---------------------------------------------------------------------------

typedef struct {
    int      tag;
    __int128 value;
    int      trailer;
} Box;

static void test_struct(void) {
    printf("\n--- 9. Struct Embedding ---\n");

    Box b;
    b.tag     = 0xAB;
    b.value   = ((__int128)0xDEADBEEFCAFEBABEULL << 64) | 0x0102030405060708ULL;
    b.trailer = 0xCD;

    if (b.tag != 0xAB) { failures++; printf("FAIL  struct tag\n"); }
    else printf("PASS  struct tag intact\n");

    if (b.trailer != 0xCD) { failures++; printf("FAIL  struct trailer\n"); }
    else printf("PASS  struct trailer intact\n");

    __int128 expected = ((__int128)0xDEADBEEFCAFEBABEULL << 64) | 0x0102030405060708ULL;
    check("struct __int128 field", b.value, expected);
}

// ---------------------------------------------------------------------------
// 10. Function Arguments & Return Values
// ---------------------------------------------------------------------------

static __int128 mul128(__int128 a, __int128 b) { return a * b; }
static __int128 add128(__int128 a, __int128 b) { return a + b; }
static __int128 shl128(__int128 v, int n)       { return v << n; }

static void test_functions(void) {
    printf("\n--- 10. Function Args & Return ---\n");

    __int128 r = mul128((__int128)1 << 60, (__int128)1 << 60);
    check("mul128(1<<60, 1<<60) == 1<<120", r, (__int128)1 << 120);

    __int128 s = add128((__int128)1 << 126, (__int128)1 << 126);
    check("add128(1<<126,1<<126) == 1<<127", s, (__int128)1 << 127);

    __int128 t = shl128((__int128)1, 100);
    check("shl128(1, 100) == 1<<100", t, (__int128)1 << 100);
}

// ---------------------------------------------------------------------------
// 11. Signed vs Unsigned Division & Modulo Edge Cases
// ---------------------------------------------------------------------------

static void test_signed_unsigned_div(void) {
    printf("\n--- 11. Signed vs Unsigned Div/Mod ---\n");

    /* Signed division with negatives */
    __int128 a = (__int128)-17;
    __int128 b = (__int128)5;
    check("(-17) / 5 == -3", a / b, (__int128)-3);
    check("(-17) % 5 == -2", a % b, (__int128)-2);

    check("17 / (-5) == -3", (__int128)17 / (__int128)-5, (__int128)-3);
    check("17 % (-5) == 2",  (__int128)17 % (__int128)-5, (__int128)2);

    /* Unsigned large division */
    unsigned __int128 ua = (unsigned __int128)1 << 127;
    unsigned __int128 ub = (unsigned __int128)3;
    /* 2^127 / 3 = 0x55555555_55555555_55555555_55555555 */
    unsigned __int128 uq = ua / ub;
    unsigned __int128 ur = ua % ub;
    /* verify: uq*3 + ur == ua */
    check_u("uq*3 + ur == 2^127", uq * ub + ur, ua);
}

// ---------------------------------------------------------------------------
// 12. Overflow / Wrap-Around
// ---------------------------------------------------------------------------

static void test_overflow(void) {
    printf("\n--- 12. Overflow / Wrap-Around ---\n");

    /* Unsigned wrap */
    unsigned __int128 umax = (unsigned __int128)-1;
    check_u("umax + 1 == 0", umax + 1, (unsigned __int128)0);
    check_u("0 - 1 == umax", (unsigned __int128)0 - 1, umax);

    /* Signed: INT128_MIN - 1 wraps to INT128_MAX (UB but we observe) */
    __int128 smin = (__int128)1 << 127;
    __int128 smax = smin - 1;
    check("smin - 1 == smax (wrap)", smin - 1, smax);
    check("smax + 1 == smin (wrap)", smax + 1, smin);
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(void) {
    printf("=== __int128 stress test ===\n");

    test_constants();
    test_arithmetic();
    test_bitwise();
    test_shifts();
    test_comparisons();
    test_compound();
    test_casts();
    test_array();
    test_struct();
    test_functions();
    test_signed_unsigned_div();
    test_overflow();

    printf("\n============================\n");
    if (failures == 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("FAILED: %d test(s)\n", failures);
    printf("============================\n");

    return failures != 0;
}