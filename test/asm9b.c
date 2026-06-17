// test_387controlword.c
// Tests that chibicc correctly handles x87 FPU control word
// inline assembly via fnstcw and fldcw.
//
// Compile & run:
//   chibicc -o test_387controlword test_387controlword.c && ./test_387controlword
//
// Expected output (all lines):
//   PASS: got_cw is non-zero
//   PASS: precision bits readable
//   PASS: set/get round-trip

#include "test.h"

// ── Functions under test ──────────────────────────────────────────────────────

unsigned short _Py_get_387controlword(void) {
    unsigned short cw;
    __asm__ __volatile__ ("fnstcw %0" : "=m" (cw));
    return cw;
}

void _Py_set_387controlword(unsigned short cw) {
    __asm__ __volatile__ ("fldcw %0" : : "m" (cw));
}

// ── x87 control-word bit definitions ─────────────────────────────────────────
// Bits [9:8]  – rounding control  (RC)
//   00 = round to nearest (even)
//   01 = round toward -∞
//   10 = round toward +∞
//   11 = round toward zero (truncate)
#define CW_RC_MASK   0x0C00u
#define CW_RC_NEAR   0x0000u
#define CW_RC_DOWN   0x0400u
#define CW_RC_UP     0x0800u
#define CW_RC_TRUNC  0x0C00u

// Bits [9:8] – precision control (PC)  [bits 8-9 in Intel manual are actually PC]
// We keep RC for the round-trip test; PC is bits [8:9] i.e. mask 0x0300.
#define CW_PC_MASK   0x0300u

// ── Helpers ───────────────────────────────────────────────────────────────────

static int tests_run    = 0;
static int tests_passed = 0;

static void check(int cond, const char *name) {
    tests_run++;
    if (cond) {
        tests_passed++;
        printf("PASS: %s\n", name);
    } else {
        printf("FAIL: %s\n", name);
    }
}

// ── Test cases ────────────────────────────────────────────────────────────────

// 1. Basic read: the control word should never be zero on a real x87.
static void test_nonzero(void) {
    unsigned short cw = _Py_get_387controlword();
    check(cw != 0, "got_cw is non-zero");
}

// 2. Structural sanity: the precision-control bits (PC, mask 0x0300) should
//    be 0x0300 by default (extended precision, 80-bit).
//    If the runtime uses double precision (e.g. some Linux setups) they will
//    be 0x0200 – either value is non-zero, so we just check non-zero.
static void test_pc_bits(void) {
    unsigned short cw = _Py_get_387controlword();
    unsigned short pc = cw & CW_PC_MASK;
    check(pc != 0, "precision bits readable");
}

// 3. Round-trip: save the original CW, write a known value, read it back,
//    then restore the original so we don't disturb the FPU state.
static void test_roundtrip(void) {
    unsigned short original = _Py_get_387controlword();

    // Build a new CW: keep all bits from original but force RC = round-toward-zero.
    unsigned short modified = (unsigned short)((original & ~CW_RC_MASK) | CW_RC_TRUNC);

    _Py_set_387controlword(modified);
    unsigned short readback = _Py_get_387controlword();

    // Restore before asserting, so a failure can't leave the FPU in a bad state.
    _Py_set_387controlword(original);

    check(readback == modified, "set/get round-trip");
}

// ── Entry point ───────────────────────────────────────────────────────────────

int main(void) {
    test_nonzero();
    test_pc_bits();
    test_roundtrip();

    printf("\n%d/%d tests passed.\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
