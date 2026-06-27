#include "test.h"

typedef struct { unsigned char a[20]; } Ty21;

Ty21 struct_test28(void) {
  return (Ty21){1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
}

int main() {
  ASSERT(1, struct_test28().a[0]);
  ASSERT(5, struct_test28().a[4]);
  ASSERT(10, struct_test28().a[9]);
  ASSERT(15, struct_test28().a[14]);
  ASSERT(20, struct_test28().a[19]);
  printf("OK\n");
  return 0;
}
