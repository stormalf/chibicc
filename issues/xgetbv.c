#include "test.h"
#include <stdint.h>

// direct wrapper for xgetbv
static inline uint64_t xgetbv(uint32_t xcr) {
    uint32_t eax, edx;
    __asm__ volatile (
        ".byte 0x0f, 0x01, 0xd0"   // xgetbv opcode
        : "=a"(eax), "=d"(edx)     // outputs in eax, edx
        : "c"(xcr)                 // input: xcr in ecx
    );
    return ((uint64_t)edx << 32) | eax;
}


static inline void cpuid(uint32_t leaf, uint32_t subleaf,
                         uint32_t *a, uint32_t *b,
                         uint32_t *c, uint32_t *d) {
    __asm__ volatile("cpuid"
                     : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                     : "a"(leaf), "c"(subleaf));
}

int main(void) {
    
    printf("Calling xgetbv(0)...\n");
    uint64_t val = xgetbv(0);
    printf("xgetbv(0) = 0x%llx\n", (unsigned long long)val);
    return 0;
}
