#include <stdio.h>
#include "test.h"
#define WITH_LIBGC

#define PRINT_ERROR(...) ((void)fprintf(stderr, __VA_ARGS__))

int main(int argc, char *argv[]) {
	PRINT_ERROR( "NIT_GC_OPTION accepts 'malloc', 'large'"
#ifdef WITH_LIBGC
					", 'boehm'"
#endif
					". Default is 0.\n");

	
	return 0;
}