#include <stdio.h>
#include <cpuid.h>

//unsigned int __get_cpuid_max(unsigned int __ext, unsigned int *__sig);

int main() {
    unsigned int sig = 0;
    unsigned int max_cpuid = __get_cpuid_max(0, &sig);

    printf("Max CPUID function: %u\n", max_cpuid);
    printf("CPU signature: %u\n", sig);

    return 0;
}
