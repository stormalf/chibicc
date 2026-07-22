/*
 * builtin_edge_test.c
 *
 * Edge-case regression test for the GCC builtins that SQLite relies on
 * once __GNUC__ is advertised as >= 4/5 (bswap, clz) or >= 5 (overflow
 * checked arithmetic), plus the __builtin_ceil/__builtin_floor pair used
 * in shell.c.
 *
 * Build with the compiler under test and with a trusted reference
 * compiler (gcc/clang), run both binaries, and diff their stdout.
 * Any line that differs identifies exactly which builtin, and which
 * edge-case input, is miscompiled.
 *
 *   cc_under_test -O0 -o edge_under_test  builtin_edge_test.c
 *   gcc            -O0 -o edge_reference  builtin_edge_test.c
 *   ./edge_under_test  > under_test.txt
 *   ./edge_reference   > reference.txt
 *   diff -u reference.txt under_test.txt
 */

#include "test.h"
#include <stdint.h>
#include <string.h>
#include <math.h>

static int g_fail = 0;

/* ---- helpers -------------------------------------------------------- */

static void report_u64(const char *name, unsigned long long got, unsigned long long want) {
    if (got != want) {
        g_fail++;
        printf("FAIL %-28s got=0x%016llx want=0x%016llx\n", name, got, want);
    } else {
        printf("ok   %-28s 0x%016llx\n", name, got);
    }
}

static void report_i64(const char *name, long long got, long long want) {
    if (got != want) {
        g_fail++;
        printf("FAIL %-28s got=%lld want=%lld\n", name, got, want);
    } else {
        printf("ok   %-28s %lld\n", name, got);
    }
}

static void report_double(const char *name, double got, double want) {
    /* bit-exact compare so -0.0 vs 0.0 and NaN payload games show up */
    unsigned long long g, w;
    memcpy(&g, &got, 8);
    memcpy(&w, &want, 8);
    /* Treat any two NaNs as equal (NaN bit patterns are not portable) */
    if (got != got && want != want) {
        printf("ok   %-28s NaN\n", name);
        return;
    }
    if (g != w) {
        g_fail++;
        printf("FAIL %-28s got=%.17g (0x%016llx) want=%.17g (0x%016llx)\n",
               name, got, g, want, w);
    } else {
        printf("ok   %-28s %.17g\n", name, got);
    }
}

/* ---- wrappers around the builtins under test ------------------------ */

static double seriesCeil(double r)  { return __builtin_ceil(r); }
static double seriesFloor(double r) { return __builtin_floor(r); }

static uint16_t bswap16_(uint16_t x) { return __builtin_bswap16(x); }
static uint32_t bswap32_(uint32_t x) { return __builtin_bswap32(x); }
static uint64_t bswap64_(uint64_t x) { return __builtin_bswap64(x); }

static unsigned int   clz32_(unsigned int m)        { return __builtin_clz(m); }
static unsigned int   clzll_(unsigned long long m)  { return __builtin_clzll(m); }

/* mirror sqlite3AddInt64/SubInt64/MulInt64 usage: overflow returns 1 and
 * leaves *pA holding the (possibly wrapped) result computed by the builtin */
static int add_ovf(long long *pA, long long iB) { return __builtin_add_overflow(*pA, iB, pA); }
static int sub_ovf(long long *pA, long long iB) { return __builtin_sub_overflow(*pA, iB, pA); }
static int mul_ovf(long long *pA, long long iB) { return __builtin_mul_overflow(*pA, iB, pA); }

/* also exercise the 32-bit and unsigned forms, since chibicc-style
 * builtins are often only tested/implemented for one width/signedness */
static int add_ovf_u64(unsigned long long *pA, unsigned long long iB) {
    return __builtin_add_overflow(*pA, iB, pA);
}
static int add_ovf_i32(int *pA, int iB) { return __builtin_add_overflow(*pA, iB, pA); }
static int mul_ovf_i32(int *pA, int iB) { return __builtin_mul_overflow(*pA, iB, pA); }

int main(void) {

    /* ---------------- __builtin_ceil / __builtin_floor ---------------- */
    report_double("ceil(0.0)",                 seriesCeil(0.0),                 0.0);
    report_double("ceil(-0.0)",                 seriesCeil(-0.0),                -0.0);
    report_double("ceil(3.2)",                 seriesCeil(3.2),                 4.0);
    report_double("ceil(-3.2)",                seriesCeil(-3.2),                -3.0);
    report_double("ceil(-0.5)",                seriesCeil(-0.5),                -0.0);
    report_double("ceil(2.0)",                 seriesCeil(2.0),                 2.0);
    report_double("ceil(4503599627370496.0)",  seriesCeil(4503599627370496.0),  4503599627370496.0); /* 2^52 */
    report_double("ceil(+inf)",                seriesCeil(1.0/0.0),             1.0/0.0);
    report_double("ceil(-inf)",                seriesCeil(-1.0/0.0),            -1.0/0.0);
    report_double("ceil(nan)",                 seriesCeil(0.0/0.0),             0.0/0.0);

    report_double("floor(0.0)",                seriesFloor(0.0),                0.0);
    report_double("floor(-0.0)",                seriesFloor(-0.0),               -0.0);
    report_double("floor(3.2)",                seriesFloor(3.2),                3.0);
    report_double("floor(-3.2)",               seriesFloor(-3.2),               -4.0);
    report_double("floor(0.5)",                seriesFloor(0.5),                0.0);
    report_double("floor(-4503599627370496.0)",seriesFloor(-4503599627370496.0),-4503599627370496.0);
    report_double("floor(+inf)",               seriesFloor(1.0/0.0),            1.0/0.0);
    report_double("floor(-inf)",               seriesFloor(-1.0/0.0),           -1.0/0.0);
    report_double("floor(nan)",                seriesFloor(0.0/0.0),            0.0/0.0);

    /* ---------------- __builtin_bswap16/32/64 -------------------------- */
    report_u64("bswap16(0x0000)", bswap16_(0x0000), 0x0000);
    report_u64("bswap16(0x00ff)", bswap16_(0x00ff), 0xff00);
    report_u64("bswap16(0x1234)", bswap16_(0x1234), 0x3412);
    report_u64("bswap16(0xffff)", bswap16_(0xffff), 0xffff);
    report_u64("bswap16(0x8000)", bswap16_(0x8000), 0x0080);

    report_u64("bswap32(0x00000000)", bswap32_(0x00000000u), 0x00000000u);
    report_u64("bswap32(0x000000ff)", bswap32_(0x000000ffu), 0xff000000u);
    report_u64("bswap32(0x12345678)", bswap32_(0x12345678u), 0x78563412u);
    report_u64("bswap32(0xffffffff)", bswap32_(0xffffffffu), 0xffffffffu);
    report_u64("bswap32(0x80000000)", bswap32_(0x80000000u), 0x00000080u);
    report_u64("bswap32(0x0000ffff)", bswap32_(0x0000ffffu), 0xffff0000u);

    report_u64("bswap64(0x0000000000000000)", bswap64_(0x0000000000000000ull), 0x0000000000000000ull);
    report_u64("bswap64(0x0123456789abcdef)", bswap64_(0x0123456789abcdefull), 0xefcdab8967452301ull);
    report_u64("bswap64(0xffffffffffffffff)", bswap64_(0xffffffffffffffffull), 0xffffffffffffffffull);
    report_u64("bswap64(0x8000000000000000)", bswap64_(0x8000000000000000ull), 0x0000000000000080ull);
    report_u64("bswap64(0x00000000ffffffff)", bswap64_(0x00000000ffffffffull), 0xffffffff00000000ull);
    report_u64("bswap64(0x000000ff00000000)", bswap64_(0x000000ff00000000ull), 0x00000000ff000000ull);

    /* ---------------- __builtin_clz / clzll ----------------------------- */
    /* NB: __builtin_clz(0) / __builtin_clzll(0) are undefined by the GCC
     * spec, so deliberately NOT tested here -- a miscompiler that special
     * cases 0 differently from a real bsr-based sequence is a separate,
     * legitimate bug class from the ones below, which all have well
     * defined results. */
    report_i64("clz32(1)",                  clz32_(1u),                  31);
    report_i64("clz32(0x80000000)",         clz32_(0x80000000u),         0);
    report_i64("clz32(0xffffffff)",         clz32_(0xffffffffu),         0);
    report_i64("clz32(0x0000ffff)",         clz32_(0x0000ffffu),         16);
    report_i64("clz32(2)",                  clz32_(2u),                  30);

    report_i64("clzll(1)",                  clzll_(1ull),                63);
    report_i64("clzll(0x8000000000000000)", clzll_(0x8000000000000000ull), 0);
    report_i64("clzll(0xffffffffffffffff)", clzll_(0xffffffffffffffffull), 0);
    report_i64("clzll(0x00000000ffffffff)", clzll_(0x00000000ffffffffull), 32);
    report_i64("clzll(0x0000000100000000)", clzll_(0x0000000100000000ull), 31);
    report_i64("clzll(2)",                  clzll_(2ull),                62);

    /* ---------------- __builtin_add_overflow (i64) ---------------------- */
    {
        long long a;
        int ovf;

        a = 1; ovf = add_ovf(&a, 2);
        report_i64("add_ovf(1,2).ovf", ovf, 0);
        report_i64("add_ovf(1,2).val", a, 3);

        a = INT64_MAX; ovf = add_ovf(&a, 0);
        report_i64("add_ovf(MAX,0).ovf", ovf, 0);
        report_i64("add_ovf(MAX,0).val", a, INT64_MAX);

        a = INT64_MAX; ovf = add_ovf(&a, 1);
        report_i64("add_ovf(MAX,1).ovf", ovf, 1);
        /* value on overflow is implementation/2's-complement wraparound;
         * still worth pinning down since sqlite depends on this exact
         * wrap behaviour in a couple of overflow-tolerant paths */
        report_i64("add_ovf(MAX,1).val", a, INT64_MIN);

        a = INT64_MIN; ovf = add_ovf(&a, -1);
        report_i64("add_ovf(MIN,-1).ovf", ovf, 1);
        report_i64("add_ovf(MIN,-1).val", a, INT64_MAX);

        a = -1; ovf = add_ovf(&a, 1);
        report_i64("add_ovf(-1,1).ovf", ovf, 0);
        report_i64("add_ovf(-1,1).val", a, 0);
    }

    /* ---------------- __builtin_sub_overflow (i64) ---------------------- */
    {
        long long a;
        int ovf;

        a = 5; ovf = sub_ovf(&a, 3);
        report_i64("sub_ovf(5,3).ovf", ovf, 0);
        report_i64("sub_ovf(5,3).val", a, 2);

        a = INT64_MIN; ovf = sub_ovf(&a, 0);
        report_i64("sub_ovf(MIN,0).ovf", ovf, 0);
        report_i64("sub_ovf(MIN,0).val", a, INT64_MIN);

        a = INT64_MIN; ovf = sub_ovf(&a, 1);
        report_i64("sub_ovf(MIN,1).ovf", ovf, 1);
        report_i64("sub_ovf(MIN,1).val", a, INT64_MAX);

        a = INT64_MAX; ovf = sub_ovf(&a, -1);
        report_i64("sub_ovf(MAX,-1).ovf", ovf, 1);
        report_i64("sub_ovf(MAX,-1).val", a, INT64_MIN);
    }

    /* ---------------- __builtin_mul_overflow (i64) ---------------------- */
    {
        long long a;
        int ovf;

        a = 6; ovf = mul_ovf(&a, 7);
        report_i64("mul_ovf(6,7).ovf", ovf, 0);
        report_i64("mul_ovf(6,7).val", a, 42);

        a = 0; ovf = mul_ovf(&a, INT64_MIN);
        report_i64("mul_ovf(0,MIN).ovf", ovf, 0);
        report_i64("mul_ovf(0,MIN).val", a, 0);

        a = INT64_MAX; ovf = mul_ovf(&a, 1);
        report_i64("mul_ovf(MAX,1).ovf", ovf, 0);
        report_i64("mul_ovf(MAX,1).val", a, INT64_MAX);

        a = INT64_MAX; ovf = mul_ovf(&a, 2);
        report_i64("mul_ovf(MAX,2).ovf", ovf, 1);

        a = INT64_MIN; ovf = mul_ovf(&a, -1);
        report_i64("mul_ovf(MIN,-1).ovf", ovf, 1);

        a = INT64_MIN; ovf = mul_ovf(&a, 1);
        report_i64("mul_ovf(MIN,1).ovf", ovf, 0);
        report_i64("mul_ovf(MIN,1).val", a, INT64_MIN);

        a = -1; ovf = mul_ovf(&a, -1);
        report_i64("mul_ovf(-1,-1).ovf", ovf, 0);
        report_i64("mul_ovf(-1,-1).val", a, 1);
    }

    /* ---------------- width/signedness variants ------------------------- */
    {
        unsigned long long ua; int ovf;
        ua = 0; ovf = add_ovf_u64(&ua, 0);
        report_i64("add_ovf_u64(0,0).ovf", ovf, 0);
        report_u64("add_ovf_u64(0,0).val", ua, 0);

        ua = 0xffffffffffffffffull; ovf = add_ovf_u64(&ua, 1);
        report_i64("add_ovf_u64(MAX,1).ovf", ovf, 1);
        report_u64("add_ovf_u64(MAX,1).val", ua, 0);

        int ia; 
        ia = INT32_MAX; ovf = add_ovf_i32(&ia, 1);
        report_i64("add_ovf_i32(MAX,1).ovf", ovf, 1);
        report_i64("add_ovf_i32(MAX,1).val", ia, INT32_MIN);

        ia = 1000000; ovf = mul_ovf_i32(&ia, 1000000);
        report_i64("mul_ovf_i32(1e6,1e6).ovf", ovf, 1); /* 10^12 doesn't fit in int32 */

        ia = 2; ovf = mul_ovf_i32(&ia, 3);
        report_i64("mul_ovf_i32(2,3).ovf", ovf, 0);
        report_i64("mul_ovf_i32(2,3).val", ia, 6);
    }

    printf("\n%s: %d failing check(s)\n", g_fail ? "SUMMARY" : "SUMMARY", g_fail);
    return g_fail ? 1 : 0;
}
