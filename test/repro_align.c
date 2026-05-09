#include <stdio.h>
#include <stddef.h>

struct S1 {
  int x __attribute__((aligned));
  int y;
};

struct __attribute__((aligned(8))) S2 {
  int a;
  int b __attribute__((aligned(64)));
};

int main() {
  printf("alignof(S1.x) = %zu (expected 16 on x86_64)\n", _Alignof(((struct S1*)0)->x));
  printf("offsetof(S1.y) = %zu (expected 16 or 32 depending on x alignment)\n", offsetof(struct S1, y));
  
  printf("alignof(struct S2) = %zu (expected 64)\n", _Alignof(struct S2));
  printf("offsetof(struct S2, b) = %zu (expected 64)\n", offsetof(struct S2, b));

  int fail = 0;
  if (_Alignof(struct S2) != 64) {
    printf("BUG: struct S2 alignment is %zu, expected 64\n", _Alignof(struct S2));
    fail = 1;
  }
  if (offsetof(struct S2, b) != 64) {
    printf("BUG: struct S2.b offset is %zu, expected 64\n", offsetof(struct S2, b));
    fail = 1;
  }
  
  // S1 tests
  // Note: GCC default alignment for __attribute__((aligned)) is 16 on x86_64 (max alignment for long double or SSE)
  // Actually GCC docs say: "default alignment for the largest numeric type".
  if (_Alignof(((struct S1*)0)->x) < 16) {
      printf("POTENTIAL BUG: S1.x alignment is %zu, expected >= 16\n", _Alignof(((struct S1*)0)->x));
      // Not necessarily a failure if chibicc has different defaults, but worth checking.
  }

  if (fail) return 1;
  printf("OK\n");
  return 0;
}
