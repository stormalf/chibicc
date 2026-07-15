#include "test.h"
#include "smmintrin.h"

int main() {
  __m128i a = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'd', 'c', 'b', 'a');
  __m128i b = _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'd', 'c', 'b', 'a');

  // pcmpistri: all valid bytes equal → first set bit at index 0
  ASSERT(0, __builtin_ia32_pcmpistri128((__v16qi)a, (__v16qi)b, 0));

  // pcmpistrm: smoke test
  __builtin_ia32_pcmpistrm128((__v16qi)a, (__v16qi)b, 0);

  // flag variants
  ASSERT(0, __builtin_ia32_pcmpistria128((__v16qi)a, (__v16qi)b, 0));
  ASSERT(1, __builtin_ia32_pcmpistric128((__v16qi)a, (__v16qi)b, 0));
  ASSERT(1, __builtin_ia32_pcmpistrio128((__v16qi)a, (__v16qi)b, 0));
  ASSERT(1, __builtin_ia32_pcmpistris128((__v16qi)a, (__v16qi)b, 0));
  ASSERT(1, __builtin_ia32_pcmpistriz128((__v16qi)a, (__v16qi)b, 0));

  // pcmpestri with explicit lengths
  ASSERT(0, __builtin_ia32_pcmpestri128((__v16qi)a, 4, (__v16qi)b, 4, 0));

  // pcmpestrm: smoke test
  __builtin_ia32_pcmpestrm128((__v16qi)a, 4, (__v16qi)b, 4, 0);

  // pcmpestri flag variants
  ASSERT(0, __builtin_ia32_pcmpestria128((__v16qi)a, 4, (__v16qi)b, 4, 0));
  ASSERT(1, __builtin_ia32_pcmpestric128((__v16qi)a, 4, (__v16qi)b, 4, 0));
  ASSERT(1, __builtin_ia32_pcmpestrio128((__v16qi)a, 4, (__v16qi)b, 4, 0));
  ASSERT(1, __builtin_ia32_pcmpestris128((__v16qi)a, 4, (__v16qi)b, 4, 0));
  ASSERT(1, __builtin_ia32_pcmpestriz128((__v16qi)a, 4, (__v16qi)b, 4, 0));

  return 0;
}
