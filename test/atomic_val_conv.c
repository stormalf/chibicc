// Preventive check: when a value-typed argument of an atomic builtin has a
// type different from the atomic element type (e.g. a float stored/added into
// an integer atomic), the value must be converted to the element type, just
// like a normal assignment.
#include "test.h"

int main() {
  _Atomic int a;

  // __atomic_store_n (float -> int)
  __atomic_store_n(&a, 1.5f, __ATOMIC_SEQ_CST);
  if (__atomic_load_n(&a, __ATOMIC_SEQ_CST) != 1) return 1;

  // __atomic_exchange_n (float -> int)
  int old = __atomic_exchange_n(&a, 2.5f, __ATOMIC_SEQ_CST);
  if (old != 1) return 2;
  if (__atomic_load_n(&a, __ATOMIC_SEQ_CST) != 2) return 3;

  // __atomic_add_fetch (float -> int)
  int r = __atomic_add_fetch(&a, 1.5f, __ATOMIC_SEQ_CST);
  if (r != 3) return 4;

  // __atomic_fetch_add (float -> int)
  old = __atomic_fetch_add(&a, 2.5f, __ATOMIC_SEQ_CST);
  if (old != 3) return 5;
  if (__atomic_load_n(&a, __ATOMIC_SEQ_CST) != 5) return 6;

  // __atomic_sub_fetch (float -> int)
  r = __atomic_sub_fetch(&a, 1.5f, __ATOMIC_SEQ_CST);
  if (r != 4) return 7;

  // __atomic_fetch_and (int -> result)
  old = __atomic_fetch_and(&a, 6, __ATOMIC_SEQ_CST);
  if (old != 4) return 8;

  return 0;
}
