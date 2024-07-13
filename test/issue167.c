#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef unsigned long int uint64;
typedef unsigned int uint32;

typedef struct pg_atomic_uint64
{
	/* alignment guaranteed due to being on a 64bit platform */
	volatile uint64 value;
} pg_atomic_uint64;

typedef struct pg_atomic_uint32
{
	volatile uint32 value;
} pg_atomic_uint32;


static inline bool
pg_atomic_compare_exchange_u64_impl(volatile pg_atomic_uint64 *ptr,
                                                                        uint64 *expected, uint64 newval)
{
        char    ret;

        /*
         * Perform cmpxchg and use the zero flag which it implicitly sets when
         * equal to measure the success.
         */
        __asm__ __volatile__(
                "       lock                            \n"
                "       cmpxchgq        %4,%5   \n"
                "   setz                %2              \n"
:               "=a" (*expected), "=m"(ptr->value), "=q" (ret)
:               "a" (*expected), "r" (newval), "m"(ptr->value)
:               "memory", "cc");
        return (bool) ret;
}

static inline bool
pg_atomic_compare_exchange_u32_impl(volatile pg_atomic_uint32 *ptr,
									uint32 *expected, uint32 newval)
{
	char	ret;

	/*
	 * Perform cmpxchg and use the zero flag which it implicitly sets when
	 * equal to measure the success.
	 */
// 	__asm__ __volatile__(
// 		"	lock				\n"
// 		"	cmpxchgl	%4,%5	\n"
// 		"   setz		%2		\n"
// :		"=a" (*expected), "=m"(ptr->value), "=q" (ret)
// :		"a" (*expected), "r" (newval), "m"(ptr->value)
// :		"memory", "cc");
	return (bool) ret;
}


int main() {
    pg_atomic_uint32 a;
    a.value = 10;
    uint32 b = 17;
    uint32 c = 0;
    pg_atomic_compare_exchange_u32_impl(&a, &b, c);


    return 0;
}