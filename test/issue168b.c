
#include "test.h"

int add2(int x, int y)
{
  return x + y;
}


int main() {
int res = 0;
int (*fn)(int,int) = add2; 
res = fn(2,5);
printf("res=%d\n", res);
ASSERT(7, res);

return 0;
}