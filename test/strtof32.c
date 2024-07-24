
#include <sys/types.h>
#include <unistd.h>
#include <features.h>
#include <stdint.h>
#include <float.h>
//#include <stdlib.h>
#define __HAVE_FLOAT32 1
#define IEC_60559_TYPES_EXT 1

# define __restrict_arr	__restrict

extern _Float32 strtof32 (const char *__restrict __nptr,
			  char **__restrict __endptr)
     __THROW __nonnull ((1));


int main(void) {
   
    return 0;
}