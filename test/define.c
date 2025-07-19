
#include "test.h"

int main() {
    int m; 
#if defined(M13)
  m = 3;
#else
  m = 4;
#endif
printf("%d\n", m);
ASSERT(4, m);
return 0;
}