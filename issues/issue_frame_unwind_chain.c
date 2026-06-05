// Minimal reproducer for test_frame_pointer_unwind failure.
//
// The CPython test test_frame_pointer_unwind expects <=1 Python frame
// in the manually unwound stack on x86_64 Linux with -O3 (omit-frame-pointer).
// chibicc -O3 currently produces 2 frames, indicating the chain is not
// being broken by the omit-fp optimization.
//
// Build:
//   ./chibicc -O3 -o /tmp/issue_frame_unwind.exe issues/issue_frame_unwind.c
//   /tmp/issue_frame_unwind.exe
//
// Reference (what GCC -O3 -fomit-frame-pointer produces):
//   length <= 3 (only this function's frame and a couple of libcs frames)
//
// chibicc -O3 currently produces: length = 5+ (chain extends too far)

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

__attribute__((noinline))
static int manual_unwind_len(void *anchor_addr) {
  uintptr_t *fp = (uintptr_t *)__builtin_frame_address(0);
  int len = 0;
  int max_iter = 200;

  for (int i = 0; i < max_iter && fp; i++) {
    uintptr_t fp_addr = (uintptr_t)fp;
    uintptr_t *next_fp = (uintptr_t *)fp[0];

    len++;

    // Break conditions matching CPython's manual_unwind_from_fp:
    if ((uintptr_t)next_fp < 4096)
      break;
    if ((uintptr_t)next_fp <= fp_addr)
      break;
    if ((uintptr_t)next_fp - fp_addr > (1u << 20))
      break;

    fp = next_fp;
  }

  (void)anchor_addr;
  return len;
}

// Simulate the call depth of CPython's build_stack(10, unwinder)
// by recursing through 10 Python-ish C frames, each calling the next.
__attribute__((noinline))
static int build_stack(int n) {
  volatile int keep = n;
  if (n == 0)
    return manual_unwind_len(NULL) + keep;
  int r = build_stack(n - 1);
  return r + (keep & 0);
}

int main(void) {
  int len = build_stack(10);
  printf("manual_unwind_len=%d\n", len);

  // With -O3 + omit-frame-pointer, the chain should be very short:
  // - this function (manual_unwind_len) keeps rbp because it uses
  //   __builtin_frame_address(0)
  // - build_stack's recursive frames (no frame_address call) should NOT
  //   push rbp, so the chain should break quickly.
  //
  // Expected: len <= 3 (this function + main + a couple of libcs)
  // Currently: chibicc -O3 produces len = 5 or more, indicating the
  // omit-fp optimization is not being applied to the recursive frames.
  if (len > 4) {
    printf("BUG: omit-frame-pointer chain too long (len=%d, expected <=4)\n", len);
    return 1;
  }

  printf("OK\n");
  return 0;
}
