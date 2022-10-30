#include <stdio.h>
#include <stdint.h>

#define HYPERVISOR_INFO_LEAF 0x40000000
#define VMWARE_BDOOR_MAGIC 0x564D5868
#define VMWARE_BDOOR_PORT 0x5658
#define VMWARE_BDOOR_CMD_GETVERSION 10

static inline void cpuid(unsigned int op, unsigned int *eax,
						 unsigned int *ebx, unsigned int *ecx,
						 unsigned int *edx)
{
	__asm__(
		"cpuid;"
		: "=b"(*ebx),
		  "=a"(*eax),
		  "=c"(*ecx),
		  "=d"(*edx)
		: "1"(op), "c"(0));
}

void vmware_bdoor(uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
	__asm__(
		"inl (%%dx), %%eax;"
		: "=b"(*ebx),
		  "=a"(*eax),
		  "=c"(*ecx),
		  "=d"(*edx)
		: "0"(VMWARE_BDOOR_MAGIC),
		  "1"(VMWARE_BDOOR_CMD_GETVERSION),
		  "2"(VMWARE_BDOOR_PORT),
		  "3"(0)
		: "memory");
}

int main(void)
{
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;
	cpuid(HYPERVISOR_INFO_LEAF, &eax, &ebx, &ecx, &edx);
	printf("%d %d %d %d\n", eax, ebx, ecx, edx);
	return 0;
}