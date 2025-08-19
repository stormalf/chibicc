// test_vectors_compound.c
#include "test.h"

typedef float  float4  __attribute__((vector_size(16)));
typedef double double2 __attribute__((vector_size(16)));
typedef int    int4    __attribute__((vector_size(16)));

int main(void) {
  // ---- FLOAT ----
  float4 a = {1.0, 2.0, 3.0, 4.0};
  float4 b = (float4){5.0, 6.0, 7.0, 8.0};

  float4 r1 = a + (float4){10.0, 10.0, 10.0, 10.0};
  float4 r2 = (float4){1.0, 1.0, 1.0, 1.0} + b;
  float4 r3 = a - (float4){1.0, 1.0, 1.0, 1.0};
  float4 r4 = (float4){2.0, 2.0, 2.0, 2.0} * b;
  float4 r5 = b / (float4){2.0, 2.0, 2.0, 2.0};  
  float4 r6 = -(float4){1.0, 2.0, 3.0, 4.0};    
  float4 r7 = -b;

  printf("float4 results:\n");
  for (int i = 0; i < 4; i++) printf("r1[%d]=%f ", i, r1[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r2[%d]=%f ", i, r2[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r3[%d]=%f ", i, r3[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r4[%d]=%f ", i, r4[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r5[%d]=%f ", i, r5[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r6[%d]=%f ", i, r6[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r7[%d]=%f ", i, r7[i]); printf("\n");

  ASSERT(11, r1[0]);
  ASSERT(12, r1[1]);
  ASSERT(13, r1[2]);
  ASSERT(14, r1[3]);

  ASSERT(6, r2[0]);
  ASSERT(7, r2[1]);
  ASSERT(8, r2[2]);
  ASSERT(9, r2[3]);

  ASSERT(0, r3[0]);
  ASSERT(1, r3[1]);
  ASSERT(2, r3[2]);
  ASSERT(3, r3[3]);

  ASSERT(10, r4[0]);
  ASSERT(12, r4[1]);
  ASSERT(14, r4[2]);
  ASSERT(16, r4[3]);

  ASSERT(2, r5[0]);
  ASSERT(3, r5[1]);
  ASSERT(3, r5[2]);
  ASSERT(4, r5[3]);

  ASSERT(-1, r6[0]);
  ASSERT(-2, r6[1]);
  ASSERT(-3, r6[2]);
  ASSERT(-4, r6[3]);

  ASSERT(-5, r7[0]);
  ASSERT(-6, r7[1]);
  ASSERT(-7, r7[2]);
  ASSERT(-8, r7[3]);
  // ---- DOUBLE ----
  double2 d1 = {1.0, 2.0};
  double2 d2 = (double2){3.0, 4.0};

  double2 dr1 = d1 + (double2){10.0, 20.0};
  double2 dr2 = (double2){2.0, 2.0} * d2;
  double2 dr3 = -(double2){5.0, 6.0}; 

  printf("\ndouble2 results:\n");
  for (int i = 0; i < 2; i++) printf("dr1[%d]=%lf ", i, dr1[i]); printf("\n");
  for (int i = 0; i < 2; i++) printf("dr2[%d]=%lf ", i, dr2[i]); printf("\n");
  for (int i = 0; i < 2; i++) printf("dr3[%d]=%lf ", i, dr3[i]); printf("\n");

  ASSERT(11, dr1[0]);
  ASSERT(22, dr1[1]);

  ASSERT(6, dr2[0]);
  ASSERT(8, dr2[1]);

  ASSERT(-5, dr3[0]);
  ASSERT(-6, dr3[1]);

  // ---- INT ----
  int4 i1 = {1, 2, 3, 4};
  int4 i2 = (int4){5, 6, 7, 8};

  int4 ir1 = i1 + (int4){10, 10, 10, 10};
  int4 ir2 = (int4){1, 1, 1, 1} + i2;
  int4 ir3 = i2 - (int4){1, 2, 3, 4}; 
  int4 ir4 = i1 * (int4){2, 2, 2, 2}; 
  int4 ir5 = -(int4){1, 2, 3, 4}; 
  int4 ir6 = i1 ^ (int4){1, 0, 1, 0}; 
  int4 ir7 = i2 & (int4){0xffffffff, 0, 0xffffffff, 0}; 
  int4 ir8 = i1 | (int4){0, 0, 0, 0xffffffff}; 

  printf("\nint4 results:\n");
  for (int i = 0; i < 4; i++) printf("ir1[%d]=%d ", i, ir1[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir2[%d]=%d ", i, ir2[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir3[%d]=%d ", i, ir3[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir4[%d]=%d ", i, ir4[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir5[%d]=%d ", i, ir5[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir6[%d]=%d ", i, ir6[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir7[%d]=%d ", i, ir7[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir8[%d]=%d ", i, ir8[i]); printf("\n");
  ASSERT(11, ir1[0]);
  ASSERT(12, ir1[1]);
  ASSERT(13, ir1[2]);
  ASSERT(14, ir1[3]);

  ASSERT(6, ir2[0]);
  ASSERT(7, ir2[1]);
  ASSERT(8, ir2[2]);
  ASSERT(9, ir2[3]);

  ASSERT(4, ir3[0]);
  ASSERT(4, ir3[1]);
  ASSERT(4, ir3[2]);
  ASSERT(4, ir3[3]);

  ASSERT(2, ir4[0]);
  ASSERT(4, ir4[1]);
  ASSERT(6, ir4[2]);
  ASSERT(8, ir4[3]);

  ASSERT(-1, ir5[0]);
  ASSERT(-2, ir5[1]);
  ASSERT(-3, ir5[2]);
  ASSERT(-4, ir5[3]);

  ASSERT(0, ir6[0]);
  ASSERT(2, ir6[1]);
  ASSERT(2, ir6[2]);
  ASSERT(4, ir6[3]);

  ASSERT(5, ir7[0]);
  ASSERT(0, ir7[1]);
  ASSERT(7, ir7[2]);
  ASSERT(0, ir7[3]);

  ASSERT(1, ir8[0]);
  ASSERT(2, ir8[1]);
  ASSERT(3, ir8[2]);
  ASSERT(-1, ir8[3]);

    // ---- INT (extra tests) ----
  int4 ir9  = ~(int4){0, -1, 0xffffffff, 1234};   // bitnot
  int4 ir10 = (int4){1, 2, 3, 4} + (int4){10, 20, 30, 40}; // compound + compound

  printf("\nint4 extra results:\n");
  for (int i = 0; i < 4; i++) printf("ir9[%d]=%d ", i, ir9[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir10[%d]=%d ", i, ir10[i]); printf("\n");

  ASSERT(-1, ir9[0]);         // ~0
  ASSERT(0,  ir9[1]);         // ~(-1) == 0
  ASSERT(0,  ir9[2]);         // ~0xffffffff == 0
  ASSERT(-1235, ir9[3]);      // ~(1234) == -1235

  ASSERT(11, ir10[0]);
  ASSERT(22, ir10[1]);
  ASSERT(33, ir10[2]);
  ASSERT(44, ir10[3]);

  printf("OK\n");

  return 0;
}
