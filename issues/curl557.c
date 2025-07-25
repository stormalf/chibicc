#include <sys/types.h>
int main() {
  switch (0) {
    case 0:
    case (sizeof(int) == 8):
    ;  // Duplicate case — should trigger error

  }
  return 0;
}
