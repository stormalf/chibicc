
#include <stdio.h>
struct {
  char c;
  char arr[];
} s = {1,2,3};
int main(void) {
    printf("%zu\n",sizeof(s)); // expected 1, got 3
    return 0;
}