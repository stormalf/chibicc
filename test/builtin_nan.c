#include <stdio.h>
float f() { return __builtin_nan(""); }

int main() {
  float f1 = f();
  printf("%f\n", f1);

  float f = __builtin_nanf("");
  double d = __builtin_nan("");
  long double ld = __builtin_nanl("");

  printf("float: %f\n", f);    // Expect: nan
  printf("double: %f\n", d);   // Expect: nan
  printf("long double: %Lf\n", ld); // Expect: nan
    return 0;
}