#include "test.h"
typedef struct pg_atomic_flag
{
	volatile char value;
} pg_atomic_flag;


pg_atomic_test_set_flag_impl(volatile pg_atomic_flag *ptr)
{
	char		_res = 1;

	__asm__ __volatile__(
		"	lock			\n"
		"	xchgb	%0,%1	\n"
:		"+q"(_res), "+m"(ptr->value)
:
:		"memory");
	ASSERT(8, _res);
	return _res == 0;
}


int main()
{
	pg_atomic_flag t = {.value= 8};
	pg_atomic_test_set_flag_impl(&t);

    return 0;
}