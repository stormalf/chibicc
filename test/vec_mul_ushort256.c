#include "test.h"
#include <stdint.h>
#include <immintrin.h>

int main() {
  __v16hu a = (__v16hu){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  __v16hu b = (__v16hu){2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

  __v16hu c = a * b;

  uint16_t out[16];
  memcpy(out, &c, sizeof(out));

  for (int i = 0; i < 16; i++)
    ASSERT((i + 1) * (i + 2), out[i]);

  printf("OK\n");
  return 0;
}
