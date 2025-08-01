
#include "test.h"
#ifdef _WIN32
#include <limits.h>
#include <intrin.h>
typedef unsigned __int32 uint32_t;
#else
#include <stdint.h>
#endif

int
main (void)
{
	uint32_t r[4] = {1, 2, 3, 4};
	uint32_t eax_in = 0x80000008U;
	uint32_t a = 7, b = 8, c = 9, d = 6;

	// uint32_t eax_out = r[0];
	// uint32_t vaddr = ((eax_out & 0x0000ff00U) >> 8);
	// FILE *f = fopen("./conftest.out", "w");
	// if (f == NULL) {
	// 	printf("f is null\n");
	// 	return 1;
	// }

#ifdef _WIN32
	__cpuid((int *)r, (int)eax_in);
#else
	asm volatile ("cpuid"
	    : "=a" (r[0]), "=b" (r[1]), "=c" (r[2]), "=d" (r[3])
	    : "a" (eax_in), "c" (0)
	);	
#endif


	printf("%d, %d, %d, %d\n", a, b, c, d);
	printf("%d, %d, %d, %d\n", r[0], r[1], r[2], r[3]);
	ASSERT(12336, r[0]);

	// if (vaddr > (sizeof(void *) << 3)) {
	// 	vaddr = sizeof(void *) << 3;
	// }
	//fprintf(f, "%u", vaddr);
	// printf("%d, %d, %d, %d\n", r[0], r[1], r[2], r[3]);
	// for (int i = 0; i < (sizeof(r)/sizeof(r[0])); i++)
	// 	printf("%d\n", r[i]);
	//fclose(f);
	return 0;

}
