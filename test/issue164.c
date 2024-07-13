
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
	return _res == 0;
}


int main()
{

    return 0;
}