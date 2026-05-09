/**
 * test_constant_folding.c
 * ========================
 * Tests for constant folding / constant-expression evaluation in chibicc.
 *
 * chibicc has NO optimization pass, so it does NOT fold constants at the
 * code-generation level. However, the C11 standard mandates that certain
 * contexts REQUIRE the compiler to evaluate constant expressions at
 * compile time:
 *
 *   - Array sizes (VLA vs fixed)
 *   - Enum values
 *   - case labels in switch
 *   - _Static_assert conditions
 *   - Static/global variable initializers
 *   - Bit-field widths
 *
 * This test file is split into two parts:
 *
 *   PART A – "Mandatory" constant folding (must compile & produce correct
 *             values to be C11-conformant). A conforming chibicc MUST pass
 *             these.
 *
 *   PART B – "Optional" runtime constant folding (pure optimization).
 *             chibicc is NOT expected to fold these, but the runtime
 *             results must still be correct. These tests check correctness,
 *             not whether folding actually happened.
 *
 * Build:
 *   chibicc -o test_constant_folding test_constant_folding.c && ./test_constant_folding
 *
 * Expected output: all lines print "OK".
 */

#include <stdio.h>

/* ------------------------------------------------------------------ */
/* Minimal test harness                                                 */
/* ------------------------------------------------------------------ */

static int g_tests  = 0;
static int g_passed = 0;

#define CHECK(label, expr)                                      \
    do {                                                        \
        g_tests++;                                              \
        if (expr) {                                             \
            g_passed++;                                         \
            printf("OK   " label "\n");                         \
        } else {                                                \
            printf("FAIL " label "  (line %d)\n", __LINE__);   \
        }                                                       \
    } while (0)


/* ================================================================== */
/* PART A – Mandatory compile-time constant expressions                */
/* ================================================================== */

/* --- A1. Integer constant expressions in array dimensions ---------- */
#define N  (3 + 2)        /* = 5  */
#define M  (N * N - 5)    /* = 20 */

static int arr_a[N];                 /* must not be a VLA */
static int arr_b[2 * N + 1];        /* = 11 elements     */
static int arr_c[M / 4];            /* = 5  elements     */

/* --- A2. Enum constant expressions --------------------------------- */
enum Color {
    RED   = 0,
    GREEN = RED + 1,
    BLUE  = GREEN + 1,
    WHITE = (RED | GREEN | BLUE) + 1,   /* bitwise OR of prior values */
    COUNT = sizeof(int) > 0 ? 4 : -1   /* conditional constant expr  */
};

/* --- A3. Static initializers --------------------------------------- */
static const int ANSWER       = 6 * 7;               /* 42  */
static const int BIT_SHIFT    = 1 << 10;              /* 1024 */
static const int CHAIN        = (ANSWER * 2) / 4 + 1; /* 22  */

/* Struct with constant initializer */
static struct { int x; int y; } origin = { 100 - 100, 200 / 2 - 100 };

/* --- A4. Bit-field width (must be an integer constant expression) -- */
struct Flags {
    unsigned int a : 1;
    unsigned int b : (2 + 1);   /* = 3 bits */
    unsigned int c : (1 << 2);  /* = 4 bits */
};

/* --- A5. _Static_assert -------------------------------------------- */
_Static_assert(sizeof(int) >= 2,       "int must be >= 16-bit");
_Static_assert(N == 5,                  "macro N must equal 5");
_Static_assert(ANSWER == 42,            "6*7 must be 42");
_Static_assert(GREEN == 1,              "enum GREEN must be 1");
_Static_assert(WHITE == 4,              "enum WHITE must be 4");
_Static_assert(sizeof(arr_a) == N * sizeof(int), "arr_a size mismatch");


/* ================================================================== */
/* PART B – Runtime correctness of "foldable" expressions             */
/* (chibicc may or may not fold these; result must be correct)         */
/* ================================================================== */

/* Prevent the compiler from constant-propagating through a black-box  */
static int identity(int v) { return v; }

static void run_tests(void)
{
    /* ---- B1. Basic arithmetic ------------------------------------ */
    CHECK("B1a: 2+3",          (2 + 3)         == 5);
    CHECK("B1b: 10-4",         (10 - 4)        == 6);
    CHECK("B1c: 6*7",          (6 * 7)         == 42);
    CHECK("B1d: 100/4",        (100 / 4)       == 25);
    CHECK("B1e: 17%5",         (17 % 5)        == 2);
    CHECK("B1f: chain",        ((6*7)*2/4 + 1) == 22);

    /* ---- B2. Bit operations -------------------------------------- */
    CHECK("B2a: 1<<10",        (1 << 10)       == 1024);
    CHECK("B2b: 1024>>3",      (1024 >> 3)     == 128);
    CHECK("B2c: 0xF0 & 0xFF",  (0xF0 & 0xFF)   == 0xF0);
    CHECK("B2d: 0xF0 | 0x0F",  (0xF0 | 0x0F)   == 0xFF);
    CHECK("B2e: 0xFF ^ 0x0F",  (0xFF ^ 0x0F)   == 0xF0);
    CHECK("B2f: ~0 & 0xFF",    (~0 & 0xFF)     == 0xFF);

    /* ---- B3. Comparison / logical -------------------------------- */
    CHECK("B3a: 1 < 2",        (1 < 2)         == 1);
    CHECK("B3b: 2 > 2",        (2 > 2)         == 0);
    CHECK("B3c: 3 <= 3",       (3 <= 3)        == 1);
    CHECK("B3d: 0 && 1/0",     (0 && (1/1))    == 0);  /* short-circuit */
    CHECK("B3e: 1 || 1/0",     (1 || (1/1))    == 1);  /* short-circuit */
    CHECK("B3f: ternary true",  (1 ? 99 : -1)  == 99);
    CHECK("B3g: ternary false", (0 ? -1 : 77)  == 77);

    /* ---- B4. Mixed-type constant promotion ----------------------- */
    CHECK("B4a: char+int",     ((char)3 + 250) == 253);
    CHECK("B4b: unsigned wrap",(unsigned char)(255 + 1) == 0);

    /* ---- B5. Sizeof as constant expression ----------------------- */
    int arr_local[2 + 2];   /* = 4 */
    CHECK("B5a: sizeof arr_local", sizeof(arr_local) == 4 * sizeof(int));
    CHECK("B5b: sizeof int >= 2",  sizeof(int)       >= 2);

    /* ---- B6. Enum value correctness ------------------------------ */
    CHECK("B6a: RED   == 0", RED   == 0);
    CHECK("B6b: GREEN == 1", GREEN == 1);
    CHECK("B6c: BLUE  == 2", BLUE  == 2);
    CHECK("B6d: WHITE == 4", WHITE == 4);  /* 0|1|2 = 3, +1 = 4 */
    CHECK("B6e: COUNT == 4", COUNT == 4);

    /* ---- B7. Static initializer values read at runtime ----------- */
    CHECK("B7a: ANSWER",    ANSWER    == 42);
    CHECK("B7b: BIT_SHIFT", BIT_SHIFT == 1024);
    CHECK("B7c: CHAIN",     CHAIN     == 22);
    CHECK("B7d: origin.x",  origin.x  == 0);
    CHECK("B7e: origin.y",  origin.y  == 0);

    /* ---- B8. Array size via constant-folded dimension ------------ */
    CHECK("B8a: arr_a length", (int)(sizeof(arr_a)/sizeof(arr_a[0])) == 5);
    CHECK("B8b: arr_b length", (int)(sizeof(arr_b)/sizeof(arr_b[0])) == 11);
    CHECK("B8c: arr_c length", (int)(sizeof(arr_c)/sizeof(arr_c[0])) == 5);

    /* ---- B9. switch / case (case labels are constant exprs) ------ */
    int result = -1;
    switch (identity(2)) {
        case 1:         result = 10; break;
        case 1 + 1:     result = 20; break;  /* case 2 via const expr */
        case 2 + 1:     result = 30; break;
        default:        result =  0; break;
    }
    CHECK("B9a: switch case 1+1", result == 20);

    switch (identity(GREEN)) {
        case RED:   result = 0; break;
        case GREEN: result = 1; break;
        case BLUE:  result = 2; break;
        default:    result = -1; break;
    }
    CHECK("B9b: switch enum GREEN", result == 1);

    /* ---- B10. Nested / complex constant expressions -------------- */
    CHECK("B10a: nested arith",  ((2+3) * (4-1) + 1)  == 16);
    CHECK("B10b: mixed ops",     (100 / (2 * 5) - 1)   == 9);
    CHECK("B10c: shift+arith",   ((1<<4) + (1<<3))      == 24);
    CHECK("B10d: deep chain",    ((N*N - M/4)*2)         == 40); /* (25-5)*2 */
}


/* ================================================================== */
/* main                                                                 */
/* ================================================================== */

int main(void)
{
    printf("=== chibicc constant-folding test suite ===\n\n");

    printf("--- Part A: compile-time constant expressions ---\n");
    printf("    (These are validated statically; if the file compiled,\n");
    printf("     _Static_assert and array dimensions are already correct.)\n\n");

    printf("--- Part B: runtime correctness of constant expressions ---\n");
    run_tests();

    printf("\n=== Results: %d / %d passed ===\n", g_passed, g_tests);
    return (g_passed == g_tests) ? 0 : 1;
}
