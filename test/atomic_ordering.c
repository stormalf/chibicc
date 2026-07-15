// Atomic orderings that are invalid on a one-way operation must be lowered to
// a valid IR ordering so the IR assembler accepts them:
//   * an acquire store is meaningless -> relaxed
//   * a release load is meaningless -> relaxed
// GCC/clang warn and treat these as relaxed, so the result must still execute.
#include "test.h"

int main() {
  _Atomic int a;
  __atomic_store_n(&a, 5, __ATOMIC_ACQUIRE);   // invalid -> relaxed
  if (__atomic_load_n(&a, __ATOMIC_RELEASE) != 5) // invalid -> relaxed
    return 1;
  // A release store and acquire load are valid and must still work.
  __atomic_store_n(&a, 7, __ATOMIC_RELEASE);
  if (__atomic_load_n(&a, __ATOMIC_ACQUIRE) != 7)
    return 2;
  return 0;
}
