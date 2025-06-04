#ifndef CHIBICC_MATH_H
#define CHIBICC_MATH_H

// Trigonometric functions
double sin(double x);
double cos(double x);
double tan(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double atan2(double y, double x);

// Hyperbolic functions
double sinh(double x);
double cosh(double x);
double tanh(double x);

// Exponential and logarithmic functions
double exp(double x);
double frexp(double x, int *exp);
double ldexp(double x, int exp);
double log(double x);
double log10(double x);
double modf(double x, double *iptr);

// Power and absolute-value functions
double pow(double x, double y);
double sqrt(double x);
double fabs(double x);
double fmod(double x, double y);

// Rounding and remainder
double floor(double x);
double ceil(double x);
double trunc(double x);
double round(double x);
double nearbyint(double x);
double rint(double x);

// Classification
extern int __fpclassify(double __value);
extern int __isnan(double __value);
extern int __isinf(double __value);
extern int __finite(double __value);

// Constants (you can define these manually or let the compiler handle them)
#define HUGE_VAL (__builtin_huge_val())
#define HUGE_VALF (__builtin_huge_valf())
#define HUGE_VALL (__builtin_huge_vall())
#define NAN (__builtin_nan(""))
#define INFINITY (__builtin_inff())

#endif // CHIBICC_MATH_H
