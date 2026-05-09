// test/math.c
#include <math.h>
#include <assert.h>
#include <float.h>

static void test_trig(void) {
  double x = 0.5;
  assert(isunordered(NAN, 1.0));
  assert(fabs(sin(x) - sinl((long double)x)) < 1e-12);
  assert(fabs(cos(x) - cosl((long double)x)) < 1e-12);
  assert(fabs(tan(x) - tanl((long double)x)) < 1e-12);

  assert(fabs(asin(sin(x)) - x) < 1e-12);
  assert(fabs(acos(cos(x)) - x) < 1e-12);
  assert(fabs(atan(tan(x)) - x) < 1e-12);
  assert(fabs(atan2(1.0, 1.0) - M_PI / 4) < 1e-12);

  
}

static void test_hyperbolic(void) {
  double x = 0.3;
  assert(fabs(tanh(x) - sinh(x) / cosh(x)) < 1e-12);
  assert(fabsl(tanhl((long double)x)) < 1.0);
  assert(fabsl(sinhl((long double)x)) > 0.0);
}

static void test_exp_log(void) {
  int e;
  double x = 8.0;
  assert(frexp(x, &e) == 0.5);
  assert(e == 4);
  assert(ldexp(0.5, 4) == x);

  double ip;
  assert(modf(3.25, &ip) == 0.25);
  assert(ip == 3.0);

  assert(fabs(log(exp(1.0)) - 1.0) < 1e-12);
  assert(fabs(log10(1000.0) - 3.0) < 1e-12);
}

static void test_power_abs(void) {
  assert(pow(2.0, 3.0) == 8.0);
  assert(sqrt(9.0) == 3.0);
  assert(fabs(-1.25) == 1.25);
  assert(fmod(5.5, 2.0) == 1.5);

  assert(cbrt(8.0) == 2.0);
  assert(asinh(0.0) == 0.0);
  assert(acosh(1.0) == 0.0);
  assert(atanh(0.0) == 0.0);
}

static void test_special(void) {
  assert(erf(0.0) == 0.0);
  assert(erfc(0.0) == 1.0);

  assert(tgamma(1.0) == 1.0);
  assert(lgamma(1.0) == 0.0);

  assert(log1p(0.0) == 0.0);
  assert(expm1(0.0) == 0.0);
}

static void test_rounding(void) {
  assert(floor(1.9) == 1.0);
  assert(ceil(1.1) == 2.0);
  assert(trunc(-1.9) == -1.0);
  assert(round(1.5) == 2.0);
  assert(rint(2.0) == 2.0);

  assert(lround(2.3) == 2);
  assert(llround(2.7) == 3);
}

static void test_minmax_next(void) {
  assert(fmax(1.0, 2.0) == 2.0);
  assert(fmin(1.0, 2.0) == 1.0);

  double x = 1.0;
  double y = nextafter(x, 2.0);
  assert(y > x);
}

static void test_classify(void) {
  assert(isnan(NAN));
  assert(isinf(INFINITY));
  assert(isfinite(1.0));
  assert(fpclassify(0.0) == FP_ZERO);
  assert(signbit(-1.0));
  assert(!signbit(1.0));

  assert(isless(1.0, 2.0));
  assert(isgreater(2.0, 1.0));
  assert(islessequal(2.0, 2.0));
  assert(isgreaterequal(2.0, 2.0));
}

int main(void) {
  test_trig();
  test_hyperbolic();
  test_exp_log();
  test_power_abs();
  test_special();
  test_rounding();
  test_minmax_next();
  test_classify();
  return 0;
}
