#include "test.h"

#define __encls_bc(leaf, b, c, retval)	     	\
  __asm__ __volatile__ ("encls\n\t"		     	\
	   : "=a" (retval)			     	\
	   : "a" (leaf), "b" (b), "c" (c)		\
	   : "cc")

#define __encls_generic(leaf, b, c, d, retval)   	\
  __asm__ __volatile__("encls\n\t"		     	\
	   : "=a" (retval), "=b" (b), "=c" (c), "=d" (d)\
	   : "a" (leaf), "b" (b), "c" (c), "d" (d)	\
	   : "cc")

extern __inline unsigned int
__attribute__((__gnu_inline__, __always_inline__, __artificial__))
_encls_u32 (const unsigned int __L, size_t __D[])
{
  enum __encls_type
  {
    __SGX_ECREATE = 0x00
  };
  enum __encls_type __T = (enum __encls_type)__L;
  unsigned int __R = 0;
  if (!__builtin_constant_p (__T))
    __encls_generic (__L, __D[0], __D[1], __D[2], __R);
  else switch (__T)
    {
    case __SGX_ECREATE:
      __encls_bc (__L, __D[0], __D[1], __R);
      break;
    default:
      break;
    }
  return __R;
}

int main() {
  printf("OK\n");
  return 0;
}
