#include "test.h"
#include <stdint.h>

typedef struct Frame { struct Frame *next; void *ret; } Frame;

#ifdef OMIT_FRAME_POINTER
#define MAX_FRAME 4
#else
#define MAX_FRAME 55
#endif

static uintptr_t get_sp(void) {
  return (uintptr_t)__builtin_frame_address(0);
}

// Measure unwind length: expects short chain when omit-fp is active
static int unwind_len(void) {
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

static int rec(int n) {
  volatile int keep = n;
  if (n == 0)
    return unwind_len() + keep;
  int r = rec(n - 1);
  return r + (keep & 0);
}

int main() {
  uintptr_t sp = get_sp();
  ASSERT(1, sp > 0);

  int len = rec(50);

  // __builtin_frame_address(0) does not force fp for level 0, so
  // functions that only call it are still eligible for omit-fp.
  // With omit-fp, the chain is short (1-3 frames); without it would
  // reach ~55 (recursion depth + helpers).
  printf("%d\n", len);
  ASSERT(1, len <= MAX_FRAME);

  (void)sp;
  return 0;
}
