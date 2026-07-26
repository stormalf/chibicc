#include "test.h"
#include <immintrin.h>

static void cpuid(unsigned int eax_in, unsigned int ecx_in,
                  unsigned int *eax, unsigned int *ebx,
                  unsigned int *ecx, unsigned int *edx) {
    __asm__ volatile (
        "cpuid"
        : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
        : "a" (eax_in), "c" (ecx_in)
    );
}

int main() {
  unsigned int eax, ebx, ecx, edx;
  cpuid(7, 0, &eax, &ebx, &ecx, &edx);
  int has_vbmi2 = !!(ecx & (1 << 6));

  if (!has_vbmi2) {
    printf("SKIP: CPU lacks AVX-512VBMI2\n");
    return 0;
  }

  __v32hi a = {0}, b = {0}, r;
  r = __builtin_ia32_vpshrd_v32hi(a, b, 3);
  r = __builtin_ia32_vpshld_v32hi(a, b, 5);

  __v16si c = {0}, d = {0}, r2;
  r2 = __builtin_ia32_vpshrd_v16si(c, d, 7);
  r2 = __builtin_ia32_vpshld_v16si(c, d, 11);

  __v8di e = {0}, f = {0}, r3;
  r3 = __builtin_ia32_vpshrd_v8di(e, f, 13);
  r3 = __builtin_ia32_vpshld_v8di(e, f, 2);

  __mmask16 k16 = 0xAAAA;
  r2 = __builtin_ia32_vpshrd_v16si_mask(c, d, 7, r2, k16);
  r2 = __builtin_ia32_vpshld_v16si_mask(c, d, 3, r2, k16);

  __mmask8 k8 = 0x55;
  r3 = __builtin_ia32_vpshrd_v8di_mask(e, f, 1, r3, k8);
  r3 = __builtin_ia32_vpshld_v8di_mask(e, f, 4, r3, k8);

  printf("OK\n");
  return 0;
}
