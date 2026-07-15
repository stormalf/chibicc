#include "test.h"

static inline int
pg_atomic_fetch_add_u32_impl(volatile int *ptr, int add_)
{
	int res;
	__asm__ __volatile__(
		"	lock				\n"
		"	xaddl	%0,%1		\n"
:		"=q"(res), "=m"(ptr)
:		"0" (add_), "m"(ptr)
:		"memory", "cc");
	return res;
}


int main() {

    printf("Ok\n");
    return 0;
}