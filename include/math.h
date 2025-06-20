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

double fma(double x, double y, double z);    // fused multiply-add (optional, used in numerics)
double copysign(double x, double y);         // result has magnitude of x and sign of y
double hypot(double x, double y);            // sqrt(x*x + y*y)
double log2(double x);                       // base-2 log
double exp2(double x);                       // base-2 exponent

int isnormal(double x);                      // non-zero and not subnormal
#define isnormal(x)  ((fpclassify(x) == FP_NORMAL))


// Classification
extern int __fpclassify(double __value);
extern int __isnan(double __value);
extern int __isinf(double __value);
extern int __finite(double __value);

// Add missing standard macros
#define isnan(x) __isnan(x)
#define isinf(x) __isinf(x)
#define isfinite(x) __finite(x)
#define fpclassify(x) __fpclassify(x)

// Constants
#define HUGE_VAL (__builtin_huge_val())
#define HUGE_VALF (__builtin_huge_valf())
#define HUGE_VALL (__builtin_huge_vall())
#define NAN (__builtin_nan(""))
#define INFINITY (__builtin_inff())

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.43429448190325182765
#define M_LN2      0.69314718055994530942
#define M_LN10     2.30258509299404568402
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.78539816339744830962
#define M_1_PI     0.31830988618379067154
#define M_2_PI     0.63661977236758134308
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.70710678118654752440

#define FP_INFINITE  1
#define FP_NAN       2
#define FP_NORMAL    3
#define FP_SUBNORMAL 4
#define FP_ZERO      5

typedef float float_t;
typedef double double_t;


#endif // CHIBICC_MATH_H
