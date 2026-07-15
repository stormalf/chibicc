// Storing a float-typed value into an integer atomic must convert the value
// to the integer element type (like a normal assignment), not feed the raw
// float register into an integer atomic store.
#include "test.h"

int main() {
  _Atomic int a;
  __atomic_store_n(&a, 1.5f, __ATOMIC_SEQ_CST);
  if (__atomic_load_n(&a, __ATOMIC_SEQ_CST) != 1)
    return 1;

  volatile float f = 3.9f;
  __atomic_store_n(&a, f * 2, __ATOMIC_SEQ_CST);
  if (__atomic_load_n(&a, __ATOMIC_SEQ_CST) != 7)
    return 2;

  return 0;
}
