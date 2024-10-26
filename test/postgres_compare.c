#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
typedef uint32_t uint32;
typedef struct {
    volatile uint32_t value;
} pg_atomic_uint32;

static inline bool
pg_atomic_compare_exchange_u32_impl(volatile pg_atomic_uint32 *ptr,
									uint32 *expected, uint32 newval)
{
	char	ret;

	/*
	 * Perform cmpxchg and use the zero flag which it implicitly sets when
	 * equal to measure the success.
	 */
	__asm__ __volatile__(
		"	lock				\n"
		"	cmpxchgl	%4,%5	\n"
		"   setz		%2		\n"
:		"=a" (*expected), "=m"(ptr->value), "=q" (ret)
:		"a" (*expected), "r" (newval), "m"(ptr->value)
:		"memory", "cc");
	return (bool) ret;
}

int main() {
    pg_atomic_uint32 atomic_var = {0};
    uint32_t expected = 0;
    uint32_t newval = 1;

    if (pg_atomic_compare_exchange_u32_impl(&atomic_var, &expected, newval)) {
        printf("Exchange succeeded\n");
    } else {
        printf("Exchange failed\n");
    }

    return 0;
}
