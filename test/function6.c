#include <stdio.h>
#include <stdarg.h>
#include "test.h"

typedef int G;   // Dummy placeholder for G type
typedef double F; // Dummy placeholder for F type

typedef struct {
  char c;  // no special alignment here
} Aligned1024;  // name kept, but no _Alignas

long double struct_test130(
    G g0, G g1, G g2, G g3, G g4,
    F f0, F f1, F f2, F f3, F f4, F f5,
    int i0, int i1, ...
) {
  va_list ap;
  va_start(ap, i1);

  long double ret = i0 + i1;
  ret += va_arg(ap, long double);     
  ASSERT(310, ret);
  ret += va_arg(ap, int);                 // read int
  ASSERT(330, ret);
  ret += va_arg(ap, Aligned1024).c;      // read struct (just its char)
  ASSERT(337, ret);
  // you can uncomment and add more va_arg calls here as needed

  va_end(ap);
  return ret;
}

int main() {
  G g_vals[5] = {1,2,3,4,5};
  F f_vals[6] = {1,2,3,4,5,6};
  Aligned1024 s = {7};

  // Call with variadic args: long double, int, Aligned1024
  long double ld = 10.5L;
  int i = 20;

  long double result = struct_test130(
    g_vals[0], g_vals[1], g_vals[2], g_vals[3], g_vals[4],
    f_vals[0], f_vals[1], f_vals[2], f_vals[3], f_vals[4], f_vals[5],
    100, 200,
    ld,        // variadic long double    
    i,         // variadic int    
    s          // variadic struct
  );

  printf("Result = %.2Lf\n", result);
  // Expected: 100 + 200 + 10.5 + 20 + 7 = 337.5
  ASSERT(337.5, result);

  return 0;
}
