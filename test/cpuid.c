#include <stdio.h>
#include <stdint.h>
#include <assert.h>

// Simple cpuid wrapper function
void cpuid(uint32_t eax_in, uint32_t ecx_in,
           uint32_t *eax, uint32_t *ebx,
           uint32_t *ecx, uint32_t *edx)
{
    __asm__ volatile (
        "cpuid"
        : "=a" (*eax),
          "=b" (*ebx),
          "=c" (*ecx),
          "=d" (*edx)
        : "a" (eax_in),
          "c" (ecx_in)
    );
}

int main(void)
{
    uint32_t eax, ebx, ecx, edx;

    // Get vendor ID (cpuid leaf 0)
    cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    char vendor[13];
    *(uint32_t*)&vendor[0] = ebx;
    *(uint32_t*)&vendor[4] = edx;
    *(uint32_t*)&vendor[8] = ecx;
    vendor[12] = '\0';

    printf("CPUID vendor: %s\n", vendor); 
    printf("Max cpuid leaf: %u\n", eax);
    assert(0 == !strncmp("GenuineIntel", vendor, strlen(vendor)));
    assert(20 == eax);

    return 0;
}
