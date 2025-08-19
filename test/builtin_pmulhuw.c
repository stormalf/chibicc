#include "test.h"

// 64-bit vectors
typedef unsigned short v4hu __attribute__((vector_size(8)));
typedef short          v4hi __attribute__((vector_size(8)));


static unsigned short hi16_mul(unsigned int a, unsigned int b) {
  // high 16 bits of the 32-bit product (unsigned)
  unsigned int prod = a * b;      // 32-bit
  return (unsigned short)(prod >> 16);
}

int main(void) {
  v4hu A = {1000, 2000, 3000, 4000};
  v4hu B = {5000, 6000, 7000, 8000};

  // builtin takes signed 16-bit vectors; cast is fine (lane-wise bits identical)
  v4hu R = (v4hu)__builtin_ia32_pmulhuw((v4hi)A, (v4hi)B);

  unsigned short *r = (unsigned short*)&R;

  unsigned short exp0 = hi16_mul(A[0], B[0]);
  unsigned short exp1 = hi16_mul(A[1], B[1]);
  unsigned short exp2 = hi16_mul(A[2], B[2]);
  unsigned short exp3 = hi16_mul(A[3], B[3]);

  printf("R = {%hu, %hu, %hu, %hu}\n", r[0], r[1], r[2], r[3]);
  ASSERT(exp0, r[0]);
  ASSERT(exp1, r[1]);
  ASSERT(exp2, r[2]);
  ASSERT(exp3, r[3]);

  printf("OK\n");
  return 0;
}
