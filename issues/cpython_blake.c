#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdbool.h>
#include <stdio.h>

#define _Py_HACL_CAN_COMPILE_VEC128 0
#define _Py_HACL_CAN_COMPILE_VEC256 0

static void __cpuid_count(int info, int subinfo,
                          int *eax, int *ebx,
                          int *ecx, int *edx) {
#if defined(__x86_64__)
    __asm__ volatile(
        "cpuid"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
        : "a"(info), "c"(subinfo)
    );
#else
    *eax = *ebx = *ecx = *edx = 0;
#endif
}

typedef struct {
    PyTypeObject *blake2b_type;
    PyTypeObject *blake2s_type;
    bool can_run_simd128;
    bool can_run_simd256;
} Blake2State;

static void
blake2module_init_cpu_features(Blake2State *state)
{
    int eax1 = 0, ebx1 = 0, ecx1 = 0, edx1 = 0;
    int eax7 = 0, ebx7 = 0, ecx7 = 0, edx7 = 0;

    __cpuid_count(1, 0, &eax1, &ebx1, &ecx1, &edx1);
    __cpuid_count(7, 0, &eax7, &ebx7, &ecx7, &edx7);

    bool avx = (ecx1 & (1 << 28)) != 0;
    bool avx2 = (ebx7 & (1 << 5)) != 0;

    bool sse = (edx1 & (1 << 25)) != 0;
    bool sse2 = (edx1 & (1 << 26)) != 0;
    bool cmov = (edx1 & (1 << 15)) != 0;

    bool sse3 = (ecx1 & (1 << 0)) != 0;
    bool sse41 = (ecx1 & (1 << 19)) != 0;
    bool sse42 = (ecx1 & (1 << 20)) != 0;

    state->can_run_simd128 = false;
    state->can_run_simd256 = false;
}

int main(void) {
    Blake2State st = {0};
    blake2module_init_cpu_features(&st);

    printf("CPU feature detection result:\n");
    printf("  can_run_simd128 = %s\n", st.can_run_simd128 ? "true" : "false");
    printf("  can_run_simd256 = %s\n", st.can_run_simd256 ? "true" : "false");

    if (st.can_run_simd256 && !st.can_run_simd128) {
        fprintf(stderr, "Invariant violated: SIMD256 requires SIMD128!\n");
        return 1;
    }

    return 0;
}
