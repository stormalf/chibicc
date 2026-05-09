#include "test.h"
#include <stdint.h>

int _Alignas(512) g1;
int _Alignas(512) g2;
char g3;
int g4;
long g5;
char g6;

int main() {
  ASSERT(1, _Alignof(char));
  ASSERT(2, _Alignof(short));
  ASSERT(4, _Alignof(int));
  ASSERT(8, _Alignof(long));
  ASSERT(8, _Alignof(long long));
  ASSERT(1, _Alignof(char[3]));
  ASSERT(4, _Alignof(int[3]));
  ASSERT(1, _Alignof(struct {char a; char b;}[2]));
  ASSERT(8, _Alignof(struct {char a; long b;}[2]));

  ASSERT(0, ({ _Alignas(char) char x, y;  (uintptr_t)&x % 1 ;  (uintptr_t)&y % 1;}));
  ASSERT(0, ({ _Alignas(long) char x, y;  (uintptr_t)&x % 8 ; (uintptr_t)&y % 8; }));
  ASSERT(0, ({ _Alignas(32) char x, y;  (uintptr_t)&x % 32 ; (uintptr_t)&y % 32; }));
  ASSERT(0, ({ _Alignas(32) int *x, *y; (uintptr_t)&x % 32 ; (uintptr_t)&y % 32; }));
  ASSERT(0, ({ struct { _Alignas(16) char x, y; } a;  (uintptr_t)&a.x % 16 ; (uintptr_t)&a.y % 16; }));
  ASSERT(8, ({ struct T { _Alignas(8) char a; }; _Alignof(struct T); }));

  ASSERT(0, (uintptr_t)&g1 % 512);
  ASSERT(0, (uintptr_t)&g2 % 512);
  ASSERT(0, (uintptr_t)&g4 % 4);
  ASSERT(0, (uintptr_t)&g5 % 8);

  ASSERT(1, ({ char x; _Alignof(x); }));
  ASSERT(4, ({ int x; _Alignof(x); }));
  ASSERT(1, ({ char x; _Alignof x; }));
  ASSERT(4, ({ int x; _Alignof x; }));

  ASSERT(1, _Alignof(char) << 31 >> 31);
  ASSERT(1, _Alignof(char) << 63 >> 63);
  ASSERT(1, ({ char x; _Alignof(x) << 63 >> 63; }));

  ASSERT(0, ({ char x[16]; (uintptr_t)&x % 16; }));
  ASSERT(0, ({ char x[17]; (uintptr_t)&x % 16; }));
  ASSERT(0, ({ char x[100]; (uintptr_t)&x % 16; }));
  ASSERT(0, ({ char x[101]; (uintptr_t)&x % 16; }));

  printf("OK\n");
  return 0;
}
