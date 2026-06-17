// Regression test: chibicc must accept -fno-optimize-sibling-calls and
// disable tail-call optimization even under -O3.
//
// CPython's stack/traceback tests rely on real C-call-stack growth in
// certain helpers (e.g. stack overflow simulation / unwinding). If chibicc
// performs tail-call optimization despite -fno-optimize-sibling-calls,
// recursion does not grow the stack.

#include <stdint.h>
#include <stdio.h>

static volatile uintptr_t min_sp;

__attribute__((noinline)) static void record_sp(void) {
  uintptr_t sp;
  asm volatile("mov %%rsp, %0" : "=r"(sp));
  if (min_sp == 0 || sp < min_sp)
    min_sp = sp;
}

__attribute__((noinline)) static void tailrec(int n) {
  record_sp();
  if (n == 0)
    return;
  tailrec(n - 1);
}

int main(void) {
  uintptr_t start_sp;
  asm volatile("mov %%rsp, %0" : "=r"(start_sp));

  min_sp = 0;
  tailrec(200);

  if (min_sp >= start_sp) {
    printf("FAIL: stack pointer didn't move (start=%lx min=%lx)\n",
           (unsigned long)start_sp, (unsigned long)min_sp);
    return 1;
  }

  // Heuristic: with real recursion, we should see at least a few KB of stack use.
  if (start_sp - min_sp < 4096) {
    printf("FAIL: recursion used too little stack (%lu bytes)\n",
           (unsigned long)(start_sp - min_sp));
    return 1;
  }

  printf("OK: recursion used %lu bytes\n", (unsigned long)(start_sp - min_sp));
  return 0;
}
