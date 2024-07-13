#include <stdio.h>
#include "test.h"

static void GetCPUInfo(int cpu_info[4], int info_type) {
  __asm__ volatile (
    "cpuid\n"
    : "=a"(cpu_info[0]), "=b"(cpu_info[1]), "=c"(cpu_info[2]), "=d"(cpu_info[3])
    : "a"(info_type), "c"(0));
    for (int i = 0; i < 4; i++) {
      printf("%d\n", cpu_info[i]);
    }

}

void mycpuinfo(void) {
  int max_cpuid_value;
  int cpu_info[4] = {1, 2, 3, 4};
  int is_intel = 0;


  // get the highest feature value cpuid supports
  GetCPUInfo(cpu_info, 0);
  max_cpuid_value = cpu_info[0];
  for (int i = 0; i < 4; i++)
    printf("%d\n", cpu_info[i]);
  ASSERT(20, cpu_info[0]);
  ASSERT(1970169159, cpu_info[1]);
  ASSERT(1818588270, cpu_info[2]);
  ASSERT(1231384169, cpu_info[3]);

}

int main() {
    mycpuinfo();

    return 0;
}