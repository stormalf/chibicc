#include <stdint.h>
#include "test.h"

__attribute__((noinline)) static size_t alloca_delta(size_t n) {
  uintptr_t before, after;
  asm volatile("mov %%rsp, %0" : "=r"(before));
  volatile char *p = alloca(n);
  p[0] = 1;
  asm volatile("mov %%rsp, %0" : "=r"(after));
  return (size_t)(before - after);
}

int main(void) {
  size_t n = 25100;
  size_t d = alloca_delta(n);
  // alloca should only round up to 16-byte alignment.
  if (d > n + 32) {
    printf("FAIL: alloca consumed %zu bytes for n=%zu\n", d, n);
    return 1;
  }
  printf("OK: alloca consumed %zu bytes for n=%zu\n", d, n);
  return 0;
}
