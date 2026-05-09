#include "test.h"

typedef struct { int a; } S;

int main() {
  S s = {1};
  const S cs = {2};
  volatile S vs = {3};
  const volatile S cvs = {4};

  // Check types of conditional expressions using __builtin_types_compatible_p
  // 1 ? s : s -> S
  ASSERT(1, __builtin_types_compatible_p(typeof(1 ? s : s), S));
  // 1 ? s : cs -> const S
  ASSERT(1, __builtin_types_compatible_p(typeof(1 ? s : cs), const S));
  // 1 ? cs : s -> const S
  ASSERT(1, __builtin_types_compatible_p(typeof(1 ? cs : s), const S));
  // 1 ? s : vs -> volatile S
  ASSERT(1, __builtin_types_compatible_p(typeof(1 ? s : vs), volatile S));
  // 1 ? cs : vs -> const volatile S
  ASSERT(1, __builtin_types_compatible_p(typeof(1 ? cs : vs), const volatile S));
  
  // Check values are preserved
  S res;
  res = 1 ? s : cs;
  ASSERT(1, res.a);
  res = 0 ? s : cs;
  ASSERT(2, res.a);

  printf("OK\n");
  return 0;
}