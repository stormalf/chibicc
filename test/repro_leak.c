#include "test.h"
int main() {
  enum { A = 5 };
  if (sizeof(enum { A = 7 })) ;
  ASSERT(5, A);
  
  void proto(enum { A = 9 });
  ASSERT(5, A);
  
  return 0;
}
