
#include "test.h"

#if defined(__x86_64__) || defined(__i386__)
#define HYPERVISOR_INFO_LEAF 0x40000000

static inline void cpuid(unsigned int op, unsigned int *eax,
                         unsigned int *ebx, unsigned int *ecx,
                         unsigned int *edx)
{
    __asm__(
#if defined(__PIC__) && defined(__i386__)
        /* x86 PIC cannot clobber ebx -- gcc bitches */
        "xchg %%ebx, %%esi;"
        "cpuid;"
        "xchg %%esi, %%ebx;"
        : "=S" (*ebx),
#else
        "cpuid;"
        : "=b" (*ebx),
#endif
          "=a" (*eax),
          "=c" (*ecx),
          "=d" (*edx)
        : "1" (op), "c"(0));
}

int main(void) {
    unsigned int eax, ebx, ecx, edx;
    cpuid(HYPERVISOR_INFO_LEAF, &eax, &ebx, &ecx, &edx);

    // Print max supported leaf
    printf("CPUID 0x%08X: max supported leaf = 0x%08X\n", HYPERVISOR_INFO_LEAF, eax);
    ASSERT(1073741835, eax);

    // Vendor ID string is EBX, ECX, EDX concatenated as ASCII
    char vendor[13];
    vendor[0] = (char)(ebx & 0xFF);
    vendor[1] = (char)((ebx >> 8) & 0xFF);
    vendor[2] = (char)((ebx >> 16) & 0xFF);
    vendor[3] = (char)((ebx >> 24) & 0xFF);
    vendor[4] = (char)(ecx & 0xFF);
    vendor[5] = (char)((ecx >> 8) & 0xFF);
    vendor[6] = (char)((ecx >> 16) & 0xFF);
    vendor[7] = (char)((ecx >> 24) & 0xFF);
    vendor[8] = (char)(edx & 0xFF);
    vendor[9] = (char)((edx >> 8) & 0xFF);
    vendor[10] = (char)((edx >> 16) & 0xFF);
    vendor[11] = (char)((edx >> 24) & 0xFF);
    vendor[12] = '\0';

    printf("Hypervisor vendor ID: '%s'\n", vendor);

    return 0;
}

#else

int main(void) {
    printf("CPUID is only supported on x86/x86_64 architectures.\n");
    return 0;
}

#endif
