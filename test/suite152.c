
#include "test.h"

#undef  line
#define line 1000


#line line
#if 1000 != __LINE__
	#error"  # line line" not work as expected 
#endif
#undef line
#define line 8
int
main()
{
	printf("line=%d\n", line);
	ASSERT(8, line);

	return 0;
}