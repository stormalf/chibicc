// Test that pointer comparison against null generates correct LLVM IR
// The bug was: icmp ne ptr %val, 0  (invalid - compare ptr with int)
// Should be:  icmp ne ptr %val, null
#include <stdio.h>

int main() {
  int x = 42;
  int *p = &x;
  int *q = 0;

  // This triggers emit_to_bool with a pointer type
  if (p)
    printf("p is non-null\n");
  else
    printf("FAIL: p should be non-null\n");

  // comparison with 0
  if (q != 0)
    printf("FAIL: q should be null\n");
  else
    printf("q is null\n");

  if (p != 0)
    printf("p is non-null (== check)\n");
  else
    printf("FAIL: p should be non-null\n");

  if (p == 0)
    printf("FAIL: p should be non-null\n");
  else
    printf("p ne null\n");

  // pointer to bool
  _Bool b = p;
  if (b)
    printf("p to bool is true\n");
  else
    printf("FAIL: p to bool should be true\n");

  _Bool c = q;
  if (c)
    printf("FAIL: q to bool should be false\n");
  else
    printf("q to bool is false\n");

  printf("all ok\n");
  return 0;
}
