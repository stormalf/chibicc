#include "test.h"

int main() {
  int x = 0;
  int old = 0;

  old = __atomic_exchange_n(&x, 7, __ATOMIC_SEQ_CST);
  ASSERT(0, old);

  int v = __atomic_load_n(&x, __ATOMIC_SEQ_CST);
  ASSERT(7, v);

  __atomic_store_n(&x, 5, __ATOMIC_SEQ_CST);
  ASSERT(5, x);

  old = __atomic_fetch_add(&x, 3, __ATOMIC_SEQ_CST);
  ASSERT(5, old);
  ASSERT(8, x);

  old = __atomic_fetch_sub(&x, 2, __ATOMIC_SEQ_CST);
  ASSERT(8, old);
  ASSERT(6, x);

  int old2 = 6;
  int r = __atomic_compare_exchange_n(&x, &old2, 9, 0,
                                      __ATOMIC_SEQ_CST,
                                      __ATOMIC_SEQ_CST);
  ASSERT(1, r);
  ASSERT(9, x);

  old2 = 7;
  r = __atomic_compare_exchange_n(&x, &old2, 10, 0,
                                  __ATOMIC_SEQ_CST,
                                  __ATOMIC_SEQ_CST);
  ASSERT(0, r);
  ASSERT(9, x);

  __atomic_thread_fence(__ATOMIC_SEQ_CST);

  // __atomic_test_and_set returns the OLD value of *p (per GCC semantics).
  // After atomic_test_and_set, *p == 1 and we get the previous value 9.
  v = __atomic_test_and_set(&x, __ATOMIC_SEQ_CST);
  ASSERT(9, v);
  ASSERT(1, x);

  __atomic_clear(&x, __ATOMIC_SEQ_CST);
  ASSERT(0, x);

  int lf = __atomic_is_lock_free(4, &x);
  ASSERT(1, lf);

  printf("OK\n");
  return 0;
}