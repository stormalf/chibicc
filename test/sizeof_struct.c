

#include "test.h"
struct {
  char c;
  char arr[];
} s = {1,2,3};
int main(void) {
    printf("%zu\n",sizeof(s)); // expected 1
    ASSERT(1, sizeof(s));
    return 0;
}