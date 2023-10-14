
#include <stdio.h>
#ifdef _WIN32
#include <limits.h>
#include <intrin.h>
typedef unsigned __int32 uint32_t;
#else
#include <stdint.h>
#endif

void asmfunc(void) {
	uint32_t eax_in = 0x80000008U;
	uint32_t r[4] = {1, 2, 3, 4};
	printf("%d, %d, %d, %d\n", r[0], r[1], r[2], r[3]);

// 	#ifdef _WIN32
// 	__cpuid((int *)r, (int)eax_in);
// #else
// 	asm volatile ("cpuid"
// 	    : "=a" (r[0]), "=b" (r[1]), "=c" (r[2]), "=d" (r[3])
// 	    : "a" (eax_in), "c" (0)
// 	);
// #endif

	for (int i = 0; i < (sizeof(r)/sizeof(r[0])); i++)
		printf("%d\n", r[i]);

}

int
main (void)
{
 
  asmfunc();
  return 0;
}
