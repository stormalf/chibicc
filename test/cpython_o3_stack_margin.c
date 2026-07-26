// Test that extended asm output operands use the correct base register
// (%rbp vs %rsp) when the function has a forced frame pointer.
// Also tests frame pointer unwind behavior at any optimization level.

#include <stdint.h>
#include <stdio.h>

typedef struct Frame { struct Frame *next; void *ret; } Frame;

#ifdef OMIT_FRAME_POINTER
# define MAX_UNWIND 10
#else
# define MIN_UNWIND 50
#endif

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

  // Test 1: Stack margin - __builtin_frame_address(0) in function with
  // extended asm must return a valid stack address. With -O3 and
  // force_frame_pointer, extended_asm must use %rbp not %rsp.
  uintptr_t fp0 = (uintptr_t)__builtin_frame_address(0);
  uintptr_t sp;
  asm volatile("mov %%rsp, %0" : "=r"(sp));
  if (fp0 < sp || fp0 - sp > 65536) {
    printf("FAIL: frame_address(0) returned %lx but rsp=%lx\n",
           (unsigned long)fp0, (unsigned long)sp);
    failed = 1;
  }

  // Test 2: Unwind length
  int len = build_stack(50);
#ifdef OMIT_FRAME_POINTER
  if (len > MAX_UNWIND) {
    printf("FAIL: expected short chain with omit-fp, got len=%d\n", len);
    failed = 1;
  }
#else
  if (len < MIN_UNWIND) {
    printf("FAIL: expected long chain with frame pointers, got len=%d\n", len);
    failed = 1;
  }
#endif

  if (failed) {
    printf("SOME TESTS FAILED\n");
    return 1;
  }
  printf("ALL TESTS PASSED\n");
  return 0;
}
