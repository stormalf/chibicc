#include <stdio.h>
#include <stdint.h>
#include "test.h"
typedef uint32_t uint32;
typedef int32_t int32;

typedef struct {
    volatile uint32_t value;
} pg_atomic_uint32;

#define PG_HAVE_ATOMIC_FETCH_ADD_U32
static inline uint32_t
pg_atomic_fetch_add_u32_impl(volatile pg_atomic_uint32 *ptr, int32 add_)
{
	uint32 res;
	__asm__ __volatile__(
		"	lock				\n"
		"	xaddl	%0,%1		\n"
:		"=q"(res), "=m"(ptr->value)
:		"0" (add_), "m"(ptr->value)
:		"memory", "cc");
	return res;
}

int main() {
    pg_atomic_uint32 atomic_var = {10};  // Initialize the atomic variable with 10
    int32_t add_value = 5;

    printf("Initial value: %u\n", atomic_var.value);

    uint32_t old_value = pg_atomic_fetch_add_u32_impl(&atomic_var, add_value);

    printf("Old value: %u\n", old_value);
    printf("New value: %u\n", atomic_var.value);
    Assert(10, old_value);
    Assert(15, atomic_var.value);
    return 0;
}
