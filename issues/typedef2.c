
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
//#include <nmmintrin.h>
typedef float float4a1 __attribute__((__vector_size__(16), __aligned__(1)));
typedef float float4;


static __inline__ float4a1
_mm_setzero_ps(void)
{
  return __extension__ (float4a1){ 0, 0, 0, 0 };
}

/* Convert the four signed 32-bit values in A and B to SPFP form.  */
extern __inline void
_mm_cvtpi32x2_ps(float4a1 __A, float4a1 __B)
{
  float4a1 __zero = (float4a1) _mm_setzero_ps ();
  
}



int main(void)
{

	return 0;
}