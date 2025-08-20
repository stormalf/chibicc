#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef struct PyTypeObject {
    const char *name;
} PyTypeObject;

typedef struct {
    PyTypeObject *blake2b_type;
    PyTypeObject *blake2s_type;
    bool can_run_simd128;
    bool can_run_simd256;
} Blake2State;

#if defined(__x86_64__) && defined(__GNUC__)
static inline void cpuid_count(uint32_t leaf, uint32_t subleaf,
                               uint32_t *eax, uint32_t *ebx,
                               uint32_t *ecx, uint32_t *edx) {
    __asm__ volatile(
        "cpuid"
        : "=a"(*eax), "=b"(*ebx), "=c"(*ecx), "=d"(*edx)
        : "a"(leaf), "c"(subleaf));
}
#else
static inline void cpuid_count(uint32_t leaf, uint32_t subleaf,
                               uint32_t *eax, uint32_t *ebx,
                               uint32_t *ecx, uint32_t *edx) {
    *eax = *ebx = *ecx = *edx = 0;
}
#endif

static void blake2module_init_cpu_features(Blake2State *state) {
    uint32_t eax1=0, ebx1=0, ecx1=0, edx1=0;
    uint32_t eax7=0, ebx7=0, ecx7=0, edx7=0;

    cpuid_count(1,0,&eax1,&ebx1,&ecx1,&edx1);
    cpuid_count(7,0,&eax7,&ebx7,&ecx7,&edx7);

    const uint32_t ECX_AVX = 1 << 28;
    const uint32_t EBX_AVX2 = 1 << 5;
    const uint32_t EDX_SSE = 1 << 25;
    const uint32_t EDX_SSE2 = 1 << 26;

    bool avx = (ecx1 & ECX_AVX) != 0;
    bool avx2 = (ebx7 & EBX_AVX2) != 0;
    bool sse = (edx1 & EDX_SSE) != 0;
    bool sse2 = (edx1 & EDX_SSE2) != 0;

    // Write flags into struct
    state->can_run_simd128 = sse && sse2;
    state->can_run_simd256 = state->can_run_simd128 && avx && avx2;
}

int main(void) {
    Blake2State state = {0};
    state.blake2b_type = NULL;
    state.blake2s_type = NULL;

    printf("Before init: simd128=%d simd256=%d\n", state.can_run_simd128, state.can_run_simd256);
    blake2module_init_cpu_features(&state);
    printf("After init: simd128=%d simd256=%d\n", state.can_run_simd128, state.can_run_simd256);

    printf("offset blake2b_type = %zu\n", offsetof(Blake2State, blake2b_type));
    printf("offset blake2s_type = %zu\n", offsetof(Blake2State, blake2s_type));
    printf("offset can_run_simd128 = %zu\n", offsetof(Blake2State, can_run_simd128));
    printf("offset can_run_simd256 = %zu\n", offsetof(Blake2State, can_run_simd256));

    return 0;
}
