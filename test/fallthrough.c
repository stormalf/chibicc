#include "test.h"

int main() {
  int state = 0;
  int c = '5'; // ASCII value of character '5'
  int arg = -1;

  switch (state) {
    case 0:
      // Simulate condition that fails (c < 0x3c or c > 0x3f), so no break
      if (c >= 0x3c && c <= 0x3f) {
        // shouldn't enter here
        break;
      }

      // fallthrough to case 1
      arg = 0;
      // no break

    case 1:
      if (c >= '0' && c <= '9') {
        arg *= 10;
        arg += c - '0';
      }
      break;
  }

  printf("arg = %d\n", arg);
  ASSERT(5, arg);
  return 0;
}
