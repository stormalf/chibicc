#include <stdio.h>
int main() {
  unsigned int a = 0xFFFFFFFF;
  unsigned int b = 1;
  // If this is folded, it must be folded correctly (TRUE)
  if ( (0xFFFFFFFFU + 1U) < 0xFFFFFFFFU )
    return 0; // Correct: overflowed
  return 1; // Incorrect: folding skipped overflow
}
