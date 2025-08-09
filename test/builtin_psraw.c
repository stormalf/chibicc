#include "test.h"
typedef short v4hi __attribute__((vector_size(8)));

int main() {
  v4hi a = (v4hi){-2, -4, 8, 16};
  v4hi count = (v4hi){1, 1, 1, 1};

  v4hi result = __builtin_ia32_psraw(a, count);

  for (int i = 0; i < 4; i++) {
    printf("%d ", result[i]);
  }
  printf("\n");

  ASSERT(-1, result[0]);
  ASSERT(-1, result[1]);
  ASSERT(0, result[2]);
  ASSERT(0, result[3]);

  printf("OK\n");
  return 0;
}
