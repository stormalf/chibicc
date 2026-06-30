// Test that __builtin_sub_overflow works when operands get
// integer-promoted to a wider type than the destination.

typedef unsigned short u16;
typedef short i16;
typedef int bool;

int main() {
  // u16 operand, i16 destination — operand is promoted to int (i32)
  // but intrinsic was being emitted at i16, causing a type mismatch.
  u16 x = 32768;
  i16 r = 0;
  bool of = __builtin_sub_overflow(0, x, &r);
  if (of != 0) return 1;
  if (r != -32768) return 2;

  x = 32769;
  of = __builtin_sub_overflow(0, x, &r);
  if (of != 1) return 3;
  if (r != 32767) return 4;

  return 0;
}
