#include "test.h"
#include <stdint.h>

__thread void* tls_var0;
__thread void* tls_var1;

static inline void* mi_prim_tls_slot(size_t slot) {
  void* res;
  const size_t ofs = (slot*sizeof(void*));

#if defined(__x86_64__)
  __asm__("movq %%fs:%1, %0"
          : "=r" (res)
          : "m" (*((void**)ofs)));
#else
  res = 0;
#endif

  return res;
}

int main() {
#if !defined(__x86_64__)
  return 0;
#else
  int a = 123;
  int b = 456;

  tls_var0 = &a;
  tls_var1 = &b;

  // Get actual FS base
  uintptr_t fs_base;
  __asm__("movq %%fs:0, %0" : "=r"(fs_base));

  // Compute slot indices
  uintptr_t addr0 = (uintptr_t)&tls_var0;
  uintptr_t addr1 = (uintptr_t)&tls_var1;

  size_t slot0 = (addr0 - fs_base) / sizeof(void*);
  size_t slot1 = (addr1 - fs_base) / sizeof(void*);

  void* p0 = mi_prim_tls_slot(slot0);
  void* p1 = mi_prim_tls_slot(slot1);

  ASSERT(&a, p0);
  ASSERT(&b, p1);

  return 0;
#endif
}
