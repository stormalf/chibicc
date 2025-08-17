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
  float4 r5 = b / (float4){2.0, 2.0, 2.0, 2.0};  // KO
  float4 r6 = -(float4){1.0, 2.0, 3.0, 4.0};    // KO

  printf("float4 results:\n");
  for (int i = 0; i < 4; i++) printf("r1[%d]=%f ", i, r1[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r2[%d]=%f ", i, r2[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r3[%d]=%f ", i, r3[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r4[%d]=%f ", i, r4[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r5[%d]=%f ", i, r5[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("r6[%d]=%f ", i, r6[i]); printf("\n");

  // ---- DOUBLE ----
  double2 d1 = {1.0, 2.0};
  double2 d2 = (double2){3.0, 4.0};

  double2 dr1 = d1 + (double2){10.0, 20.0};
  double2 dr2 = (double2){2.0, 2.0} * d2;
  double2 dr3 = -(double2){5.0, 6.0}; // KO

  printf("\ndouble2 results:\n");
  for (int i = 0; i < 2; i++) printf("dr1[%d]=%lf ", i, dr1[i]); printf("\n");
  for (int i = 0; i < 2; i++) printf("dr2[%d]=%lf ", i, dr2[i]); printf("\n");
  for (int i = 0; i < 2; i++) printf("dr3[%d]=%lf ", i, dr3[i]); printf("\n");

  // ---- INT ----
  int4 i1 = {1, 2, 3, 4};
  int4 i2 = (int4){5, 6, 7, 8};

  int4 ir1 = i1 + (int4){10, 10, 10, 10};
  int4 ir2 = (int4){1, 1, 1, 1} + i2;
  int4 ir3 = i2 - (int4){1, 2, 3, 4}; // KO
  int4 ir4 = i1 * (int4){2, 2, 2, 2}; // KO
  int4 ir5 = -(int4){1, 2, 3, 4}; //KO
  int4 ir6 = i1 ^ (int4){1, 0, 1, 0}; // KO
  int4 ir7 = i2 & (int4){0xffffffff, 0, 0xffffffff, 0}; //KO 
  int4 ir8 = i1 | (int4){0, 0, 0, 0xffffffff}; // KO

  printf("\nint4 results:\n");
  for (int i = 0; i < 4; i++) printf("ir1[%d]=%d ", i, ir1[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir2[%d]=%d ", i, ir2[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir3[%d]=%d ", i, ir3[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir4[%d]=%d ", i, ir4[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir5[%d]=%d ", i, ir5[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir6[%d]=%d ", i, ir6[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir7[%d]=%d ", i, ir7[i]); printf("\n");
  for (int i = 0; i < 4; i++) printf("ir8[%d]=%d ", i, ir8[i]); printf("\n");

  return 0;
}
