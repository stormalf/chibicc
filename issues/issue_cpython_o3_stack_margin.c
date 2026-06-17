// Reproducer for CPython O3: stack margin miscalculation
// and frame pointer unwind failures when omit-fp is active.
//
// Build/run:
//   ./chibicc -O3 issues/issue_cpython_o3_stack_margin.c -o /tmp/issue && /tmp/issue

#include <stdint.h>
#include <stdio.h>

#define STACK_MARGIN 16384

// get_stack_pointer forces a frame pointer via __builtin_frame_address(0)
__attribute__((noinline)) static uintptr_t get_stack_pointer(void) {
  return (uintptr_t)__builtin_frame_address(0);
}

// omit-fp recursive function (no __builtin_frame_address call)
__attribute__((noinline)) static int recurse(int n) {
  volatile int keep = n;
  if (n == 0)
    return (int)get_stack_pointer() + keep;
  int r = recurse(n - 1);
  return r + (keep & 0);
}

// Manual frame-pointer unwinding
typedef struct Frame { struct Frame *next; void *ret; } Frame;

__attribute__((noinline)) static int unwind_len(void) {
  Frame *fp = (Frame *)__builtin_frame_address(0);
  int n = 0;
  while (fp && n < 256) {
    Frame *next = fp->next;
    n++;
    if (!next) break;
    if ((uintptr_t)next <= (uintptr_t)fp) break;
    if ((uintptr_t)next - (uintptr_t)fp > (1u << 20)) break;
    fp = next;
  }
  return n;
}

__attribute__((noinline)) static int build_stack(int n) {
  volatile int keep = n;
  if (n == 0)
    return unwind_len();
  int r = build_stack(n - 1);
  return r + (keep & 0);
}

int main(void) {
  int failed = 0;

  // Test 1: Stack margin
  uintptr_t sp0 = get_stack_pointer();
  (void)sp0; // baseline
  int r = recurse(10);
  (void)r;

  // Test 2: Unwind length with omit-fp recursive frames
  int len = build_stack(50);
  printf("unwind_len=%d\n", len);

  // With omit-fp, the chain should be short (~3-5 frames) because
  // recursive frames don't push %rbp.
  // With frame pointers, it would be ~54 (50 recursive + 4).
  if (len > 10) {
    printf("FAIL: frame_pointer_unwind - expected short chain, got len=%d\n", len);
    failed = 1;
  }

  // Test 3: __builtin_frame_address(0) in omit-fp vs non-omit-fp
  // Verify level 0 returns a reasonable address on the stack
  uintptr_t fp0 = (uintptr_t)__builtin_frame_address(0);
  uintptr_t sp;
  asm volatile("mov %%rsp, %0" : "=r"(sp));
  // fp0 should be >= sp (above on stack) and within reasonable range
  if (fp0 < sp || fp0 - sp > 65536) {
    printf("FAIL: frame_address(0) returned %lx but rsp=%lx\n",
           (unsigned long)fp0, (unsigned long)sp);
    failed = 1;
  }

  // Test 4: __builtin_frame_address(n) for n>0 with omit-fp
  void *fp1 = __builtin_frame_address(1);
  void *fp2 = __builtin_frame_address(2);
  if (!fp1 || !fp2) {
    printf("Note: frame_address(1)=%p frame_address(2)=%p (NULL means omit-fp broke chain)\n", fp1, fp2);
  }

  if (failed) {
    printf("SOME TESTS FAILED\n");
    return 1;
  }
  printf("ALL TESTS PASSED\n");
  return 0;
}
