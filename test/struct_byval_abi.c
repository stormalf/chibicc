#include "test.h"

// Regression test for the AMD64 SysV struct-by-value ABI in the LLVM backend.
// chibicc used to pass every struct-by-value argument as a hidden pointer and
// return every struct by value through a hidden sret pointer, which only worked
// between chibicc translation units and broke at any real (libc/asm/gcc)
// boundary.  This exercises small aggregates of every size class (1..16 bytes,
// including odd sizes that do not fill an eightbyte) passed and returned by
// value, with integer and floating-point members, so a regression of the
// register/byval lowering is caught by the produced values.

typedef struct { unsigned char a; } S1;
typedef struct { unsigned short a; } S2;
typedef struct { unsigned char a[3]; } S3;
typedef struct { int a; } S4;
typedef struct { long a; long b; } S16;
typedef struct { int a; int b; int c; } S12;
typedef struct { int a; float b; } SF8;
typedef struct { float a; float b; float c; float d; } SF16;

S1 mk_s1(unsigned char v) { S1 r; r.a = v; return r; }
S2 mk_s2(unsigned short v) { S2 r; r.a = v; return r; }
S3 mk_s3(unsigned char a, unsigned char b, unsigned char c) {
  S3 r; r.a[0] = a; r.a[1] = b; r.a[2] = c; return r;
}
S4 mk_s4(int v) { S4 r; r.a = v; return r; }
S16 mk_s16(long a, long b) { S16 r; r.a = a; r.b = b; return r; }
S12 mk_s12(int a, int b, int c) { S12 r; r.a = a; r.b = b; r.c = c; return r; }
SF8 mk_sf8(int a, float b) { SF8 r; r.a = a; r.b = b; return r; }
SF16 mk_sf16(float a, float b, float c, float d) {
  SF16 r; r.a = a; r.b = b; r.c = c; r.d = d; return r;
}

int use_s1(S1 x) { return x.a; }
int use_s2(S2 x) { return x.a; }
int use_s3(S3 x) { return x.a[0] * 100 + x.a[1] * 10 + x.a[2]; }
int use_s4(S4 x) { return x.a; }
long use_s16(S16 x) { return x.a + x.b; }
int use_s12(S12 x) { return x.a + x.b + x.c; }
int use_sf8(SF8 x) { return x.a + (int)x.b; }
float use_sf16(SF16 x) { return x.a + x.b + x.c + x.d; }

int main() {
  ASSERT(99, use_s1(mk_s1(99)));
  ASSERT(0x1234, use_s2(mk_s2(0x1234)));
  ASSERT(321, use_s3(mk_s3(3, 2, 1)));
  ASSERT(555, use_s4(mk_s4(555)));
  S16 s16 = mk_s16(40, 59);
  ASSERT(99, use_s16(s16));
  ASSERT(40, s16.a);
  ASSERT(59, s16.b);
  S12 s12 = mk_s12(10, 20, 69);
  ASSERT(99, use_s12(s12));
  ASSERT(69, s12.c);
  ASSERT(130, use_sf8(mk_sf8(100, 30.0f)));
  ASSERT(10, (int)use_sf16(mk_sf16(1.0f, 2.0f, 3.0f, 4.0f)));

  // Mixed argument registers: a small struct in between integer arguments
  // must not corrupt the surrounding scalar arguments.
  ASSERT(10, use_s12((S12){1, 2, 3}) + 4);
  return 0;
}
