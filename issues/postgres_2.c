#include <unicode/ucol.h>
#include <unicode/platform.h>

#define U_CAPI U_CFUNC U_EXPORT
#   define U_EXPORT __attribute__((visibility("default")))