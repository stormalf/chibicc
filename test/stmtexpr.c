#include "test.h"
#include <stdio.h>
struct S {
  int a, b;
};
int main() {
  struct S s1 = {11,-22 };
  printf(" %d \n", sizeof ({ int arr[17]; arr; }) );
  printf(" %d \n", sizeof ({ int arr[s1.a]; arr; }) );
  ASSERT(-22, ({ ({ s1; }); }).b );
  ASSERT(11, ({ ({ struct S s2 = s1; s2; }).a; }));
  ASSERT(-22, ({ ({ struct S s2 = s1; s2; }); }).b );
  ASSERT(11, ({ ({(struct S){11,22}; }).a; }));
  ASSERT(22, ({ ({(struct S){11,22}; }); }).b );
  ASSERT(68, sizeof ({ int arr[17]; arr; }) );
  //ASSERT(0, sizeof ({ int arr[s1.a]; arr; }) );
  printf("OK\n");
  return 0;
}