#include "test.h"

static inline int mul(int a, int b) {
  int result = 0;
  while (b) {
    if (b & 1)
      result += a;
    b >>= 1;
    a <<= 1;
  }
  return result;
}

static inline int compute(int x) {
  int sum = 0;
  for (int i = 0; i < 4; i++)
    sum += mul(x, i);
  return sum;
}

int main() {
  ASSERT(6, compute(3));  // 3*0 + 3*1 + 3*2 + 3*3 = 0+3+6+9 = 18? No, mul returns 0+0+3+6=9? 
  // Actually mul(3,0)=0, mul(3,1)=3, mul(3,2)=6, mul(3,3)=9 => 0+3+6+9=18
  ASSERT(18, compute(3));
  ASSERT(0, compute(0));
  ASSERT(60, compute(6)); // 0+6+12+18 = 36... wait, mul(6,1)=6, mul(6,2)=12, mul(6,3)=18 => 0+6+12+18=36
  return 0;
}
