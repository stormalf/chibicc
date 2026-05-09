#include "test.h"

#ifndef __has_builtin
#error
#endif

#if !__has_builtin(__builtin_offsetof)
#error
#endif

#define HB __has_builtin
#define NAME __builtin_offsetof
#define WRAP(x) x

#if !HB(NAME)
#error
#endif

// Macro expansion inside argument should be accepted.
#if !__has_builtin(__builtin_offsetof)
#error
#endif

// Macro expansion inside argument should be accepted.
#if !__has_builtin(WRAP(__builtin_offsetof))
#error
#endif

int main(void) {
  printf("OK\n");
  return 0;
}
