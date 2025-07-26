#include "test.h"

#define THREAD_LOCAL static __thread
int uuid_generate_time_generic() {
	const int			cs_min = 1<<6;
	const int			cs_max = (1<<18);
	const int			cs_factor = 2;
	THREAD_LOCAL int		num = 0;
    THREAD_LOCAL int		cache_size = cs_min;
    //int		cache_size = cs_min;
return cs_min;
}

int main() {
	int a = uuid_generate_time_generic();
	printf("a=%d\n", a);
	ASSERT(64, a);
    return 0;
}