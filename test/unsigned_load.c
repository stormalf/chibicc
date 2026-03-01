#include "test.h"
#include <stddef.h>

typedef unsigned int Oid;
struct T {
    int a;
    long b;
    int c;
};


int main() {
  // Test 1: Unsigned int with high bit set (0x80000000)
  // When loaded into a 64-bit register, it should be zero-extended.
  unsigned int u = 0x80000000;
  unsigned long long lu = u;
  
  // If sign-extended (movsxd), 0x80000000 becomes 0xFFFFFFFF80000000
  // If zero-extended (mov), 0x80000000 becomes 0x0000000080000000
  ASSERT(2147483648, lu);

  // Test 2: Signed int with high bit set (negative)
  // Should be sign-extended.
  int s = -2147483648; 
  long long ls = s;
  ASSERT(-2147483648, ls);

  // Test 3: Oid type (unsigned int)
  Oid oid = 0xF0000000;
  unsigned long datum = (unsigned long)oid;
  // 0xF0000000 = 4026531840
  ASSERT(4026531840, datum);

  // Test 4: Explicit cast behavior
  unsigned int u2 = 0xFFFFFFFF;
  long long l2 = (long long)u2;
  ASSERT(4294967295, l2);


  printf("sizeof(int)=%zu\n", sizeof(int));
  printf("sizeof(unsigned int)=%zu\n", sizeof(unsigned int));
  printf("sizeof(long)=%zu\n", sizeof(long));
  printf("sizeof(void*)=%zu\n", sizeof(void*));
  printf("sizeof(enum { A })=%zu\n", sizeof(enum { A }));
  printf("offsetof(a)=%zu\n", offsetof(struct T, a));
  printf("offsetof(b)=%zu\n", offsetof(struct T, b));
  printf("offsetof(c)=%zu\n", offsetof(struct T, c));
  printf("sizeof=%zu\n", sizeof(struct T));
  unsigned int x = 0xffffffffu;
  printf("%u\n", x);
  if (x > 0)
    puts("ok");
  else
    printf("KO\n");

  printf("OK\n");
  return 0;
}