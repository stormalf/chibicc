#include <stdio.h>
float add_float(float x, float y) {
  return x + y;
}
int main() {
  float r = add_float(2.3, 3.8);
  printf("%f\n", r);
}
