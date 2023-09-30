#include <stdio.h>

typedef struct StRegSized {
    unsigned char r;
} StRegSized;

void func1(int a, int b, int c, int d, StRegSized st) {
  printf("%d %d %d %d %d\n", a, b, c, d, st.r);
}

int main(void) {
  StRegSized x = {99};
  func1(1, 2, 3, 4, x);
}