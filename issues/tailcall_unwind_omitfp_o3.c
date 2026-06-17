#include <stdint.h>
#include <stdio.h>

// Repro: GCC at -O3 -fomit-frame-pointer can shrink the manual frame-pointer
// chain via sibling-call optimization. chibicc should match this behavior when
// invoked with the same flags.
//
// Run with:
//   gcc -o /tmp/tailcall_unwind_gcc.exe issues/tailcall_unwind_omitfp_o3.c -O3 -fomit-frame-pointer
//   /tmp/tailcall_unwind_gcc.exe
//
//   ./chibicc -o /tmp/tailcall_unwind_chibicc.exe issues/tailcall_unwind_omitfp_o3.c -O3 -fomit-frame-pointer
//   /tmp/tailcall_unwind_chibicc.exe

typedef struct Frame {
  struct Frame *next;
  void *ret;
} Frame;

__attribute__((noinline)) static int unwind_len(void) {
  Frame *fp = (Frame *)__builtin_frame_address(0);
  int n = 0;

  while (fp && n < 256) {
    Frame *next = fp->next;
    n++;

    if (!next)
      break;
    if ((uintptr_t)next <= (uintptr_t)fp)
      break;
    if ((uintptr_t)next - (uintptr_t)fp > (1u << 20))
      break;

    fp = next;
  }

  return n;
}

__attribute__((noinline)) static int leaf(void) {
  volatile void *fp = __builtin_frame_address(0);
  (void)fp;
  return unwind_len();
}

__attribute__((noinline)) static int tail(void) {
  return leaf();
}

int main(void) {
  int n = tail();
  printf("%d\n", n);

  // With sibling-call optimization, GCC (x86-64 SysV) typically produces 3 here
  // under -O3 -fomit-frame-pointer. chibicc currently produces 5 because it
  // doesn't tail-call when the current function has locals/stack usage.
  if (n > 3)
    return 1;
  return 0;
}

