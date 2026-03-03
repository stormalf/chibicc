#include "test.h"

// Simple offset helper that works in constant expressions.
#define OFFSETOF(T, M) ((unsigned long)&(((T *)0)->M))

struct DefaultLayout {
  char c;
  int x;
};

#pragma pack(push, 1)
struct Pack1 {
  char c;
  int x;
  short y;
};

// Regression shape from csmith seed 27522.
struct S0Packed {
  const int f0;
  unsigned short f1;
  unsigned int f2;
  short f3;
  volatile unsigned char f4;
  signed char f5;
};

union U2Packed {
  unsigned long long f0;
  struct S0Packed f4;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct NestPack1 {
  char c;
  int x;
};

#pragma pack(push, 2)
struct NestPack2 {
  char c;
  int x;
  short y;
};
#pragma pack(pop)

struct NestBackToPack1 {
  char c;
  int x;
};
#pragma pack(pop)

struct BackToDefault {
  char c;
  int x;
};

static union U2Packed g_u2 = {.f0 = 0x1B57FCB2553E1D3EULL};

int main(void) {
  SASSERT(sizeof(int) == 4);
  SASSERT(sizeof(short) == 2);
  SASSERT(sizeof(unsigned int) == 4);

  ASSERT(8, sizeof(struct DefaultLayout));
  ASSERT(4, _Alignof(struct DefaultLayout));
  ASSERT(4, OFFSETOF(struct DefaultLayout, x));

  ASSERT(7, sizeof(struct Pack1));
  ASSERT(1, _Alignof(struct Pack1));
  ASSERT(1, OFFSETOF(struct Pack1, x));
  ASSERT(5, OFFSETOF(struct Pack1, y));

  ASSERT(14, sizeof(struct S0Packed));
  ASSERT(1, _Alignof(struct S0Packed));
  ASSERT(6, OFFSETOF(struct S0Packed, f2));
  ASSERT(6999, g_u2.f4.f2);

  ASSERT(5, sizeof(struct NestPack1));
  ASSERT(1, _Alignof(struct NestPack1));
  ASSERT(1, OFFSETOF(struct NestPack1, x));

  ASSERT(8, sizeof(struct NestPack2));
  ASSERT(2, _Alignof(struct NestPack2));
  ASSERT(2, OFFSETOF(struct NestPack2, x));
  ASSERT(6, OFFSETOF(struct NestPack2, y));

  ASSERT(5, sizeof(struct NestBackToPack1));
  ASSERT(1, _Alignof(struct NestBackToPack1));
  ASSERT(1, OFFSETOF(struct NestBackToPack1, x));

  ASSERT(8, sizeof(struct BackToDefault));
  ASSERT(4, _Alignof(struct BackToDefault));
  ASSERT(4, OFFSETOF(struct BackToDefault, x));

  return 0;
}
