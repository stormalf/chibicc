#include "test.h"
#include <stdarg.h>

typedef struct {
  char g;
} G;

typedef struct {
  float f;
} F;

typedef struct {
  char l;
  float d;
} A;


typedef struct {
  char _Alignas(1024) c;
} Aligned1024;
//extern int struct_test131(G g0,G g1,G g2,G g3,G g4,F f0,F f1,F f2,F f3,F f4,F f5,int i0,int i1,...);
int struct_test130(G g0,G g1,G g2,G g3,G g4,F f0,F f1,F f2,F f3,F f4,F f5,int i0,int i1,...) {
  va_list ap;
  va_start(ap, i1);
  long double ret = i0 + i1;
  ret += va_arg(ap, long double);
  //ret += va_arg(ap, Aligned1024).c;
  ret += va_arg(ap, int);
  //ret += va_arg(ap, double);
  //ret += va_arg(ap, double);
  //ret += va_arg(ap, double);
  //ret += va_arg(ap, double);
  //ret += va_arg(ap, Aligned1024).c;
  //ret += va_arg(ap, long double);
  va_end(ap);
  return ret;
}


int main(void) {
  G g[] = {10,11,12,13,14,15};
  F f[] = {20,21,22,23,24,25,26,27};
  G gs[]  = {30,31};
  F fs[]  = {40,41};

Aligned1024 s = {.c = 77};

  ASSERT(43, struct_test130(
    g[0], g[1], g[2], g[3], g[4],
    f[0], f[1], f[2], f[3], f[4], f[5],
    (int) 11,
    (int) 22,
    (long double) 2.3,
    //(Aligned1024) s,
    (int) 33
    //(double) 4.5,
    //(double) 5.6,
    //(double) 6.7,
    //(double) 7.8
    //(Aligned1024) s
    //(long double) 11.1
    ) );

    // ASSERT(257, struct_test131(
    // g[0], g[1], g[2], g[3], g[4],
    // f[0], f[1], f[2], f[3], f[4], f[5],
    // (int) 11,
    // (int) 22,
    // //(long double) 2.3,
    // //(Aligned1024) s,
    // (int) 33,
    // (double) 4.5,
    // (double) 5.6,
    // (double) 6.7,
    // (double) 7.8
    // //(Aligned1024) s
    // //(long double) 11.1
    // ));

  printf("OK\n");

}