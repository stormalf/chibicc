#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* Provide definition for setup function if missing from standalone assembly link */
void OPENSSL_cpuid_setup(void) {}

void OPENSSL_ia32_cpuid(uint64_t *out);

static void fill_guard(uint8_t *p, size_t n)
{
    for (size_t i = 0; i < n; i++)
        p[i] = 0xAA;
}

static int check_guard(const uint8_t *p, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (p[i] != 0xAA)
            return 0;
    return 1;
}

int main(int argc, char **argv)
{
    uint64_t out[4];
    uint8_t  guard_before[64];
    uint8_t  guard_after[64];
    printf("%d\n", argc);
    // Protect against stack overwrite detection
    fill_guard(guard_before, sizeof(guard_before));
    fill_guard(guard_after, sizeof(guard_after));

    memset(out, 0, sizeof(out));

    uint64_t rbx_before;
    __asm__ volatile ("mov %%rbx, %0" : "=r"(rbx_before));

    OPENSSL_ia32_cpuid(out);

    uint64_t rbx_after;
    __asm__ volatile ("mov %%rbx, %0" : "=r"(rbx_after));

    printf("out[0]=0x%llx out[1]=0x%llx\n",
           (unsigned long long)out[0],
           (unsigned long long)out[1]);

    if (rbx_before != rbx_after) {
        printf("❌ RBX corrupted!\n");
        return 1;
    }

    if (!check_guard(guard_before, sizeof(guard_before)) ||
        !check_guard(guard_after, sizeof(guard_after))) {
        printf("❌ Stack corruption detected!\n");
        return 1;
    }

    printf("✅ CPUID OK\n");
    return 0;
}
