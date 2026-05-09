#include "test.h"
// test_const_if.c
extern int ossl_fips_intern_provider_init(void);

int foo(void) {
    if (0)
        return ossl_fips_intern_provider_init();
    return 1;
}

// test_pp_macro.c
#define USE_FIPS 0

extern int ossl_fips_intern_provider_init3(void);

int foo3(void) {
#if USE_FIPS
  return ossl_fips_intern_provider_init3();
#else
  return 7;
#endif
}

// test_pp_if0.c
extern int ossl_fips_intern_provider_init2(void);

int foo2(void) {
#if 0
  return ossl_fips_intern_provider_init2();
#else
  return 42;
#endif
}

// test_pp_if1.c
extern int ossl_fips_intern_provider_init4(void);

int foo4(void) {
#if 1
  return 0;
#else
  return ossl_fips_intern_provider_init4();
  
#endif
}

int main(void) {
    int x;
    x = foo();
    printf("x = %d\n", x);
    ASSERT(1, x);
    x = foo2();
    printf("x = %d\n", x);
    ASSERT(42, x);
    x = foo3();
    printf("x = %d\n", x);
    ASSERT(7, x);
    x = foo4();
    printf("x = %d\n", x);
    ASSERT(0, x);

    return 0;
}