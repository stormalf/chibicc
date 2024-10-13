#include "test.h"
#include <stdio.h>

int main(void) {
  char arr[3] = {11, 22, 33};
  int i;
  i = (&arr)[0][2], printf("%d\n", i); // 33
  ASSERT(33, i);

  i = (*&arr)[1], printf("%d\n", i); // 22
  ASSERT(22, i);
  i = (**&arr), printf("%d\n", i); // 11
  ASSERT(11, i);
}
