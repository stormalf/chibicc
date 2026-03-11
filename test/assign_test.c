// issues/assign_rhs_first_gain.c
#include <stdint.h>
#include <stdio.h>

static uintptr_t top_fp;
static uintptr_t deep_fp;

__attribute__((noinline))
static uintptr_t fp(void) {
  return (uintptr_t)__builtin_frame_address(0);
}

__attribute__((noinline))
static int rec(int n) {
  volatile int x = 0;   // forces an addressable LHS
  if (n == 0) {
    deep_fp = fp();
    return 1;
  }
  x = rec(n - 1);       // this is the key ND_ASSIGN shape
  return x + 1;
}

int main(void) {
  top_fp = fp();
  rec(300);
  uintptr_t delta = top_fp > deep_fp ? top_fp - deep_fp : deep_fp - top_fp;
  printf("fp_delta=%lu\n", (unsigned long)delta);
  return 0;
}
