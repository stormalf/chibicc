#include "test.h"
typedef short v4hi __attribute__((vector_size(8)));

int main() {
  v4hi a = (v4hi){-4, -8, 16, 32};
  int count = 2;

  v4hi result = __builtin_ia32_psrawi(a, count);

  for (int i = 0; i < 4; i++) {
    printf("%d ", result[i]);
  }
  printf("\n");

  ASSERT(-1, result[0]);
  ASSERT(-2, result[1]);
  ASSERT(4, result[2]);
  ASSERT(8, result[3]);
  result = __builtin_ia32_psrawi(a, 2);
  ASSERT(-1, result[0]);
  ASSERT(-2, result[1]);
  ASSERT(4, result[2]);
  ASSERT(8, result[3]);
  printf("OK\n");
  return 0;
}
