
#include <stddef.h>
#include "test.h"
#define SIZEOF_SIZE_T 8
/* Mask to quickly check whether a C 'size_t' contains a
   non-ASCII, UTF8-encoded char. */
#if (SIZEOF_SIZE_T == 8)
# define UCS1_ASCII_CHAR_MASK 0x8080808080808080ULL
#elif (SIZEOF_SIZE_T == 4)
# define UCS1_ASCII_CHAR_MASK 0x80808080U
#else
# error C 'size_t' size should be either 4 or 8!
#endif

int main() {
  printf("%zu %zu\n", sizeof(size_t), sizeof(void *));  
  ASSERT(8, sizeof(size_t));
  int x = 'abcdef';
  return 0;
}
