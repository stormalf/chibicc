#include <unicode/ucol.h>
#include <unicode/platform.h>

#define U_CAPI U_CFUNC U_EXPORT
#   define U_EXPORT __attribute__((visibility("default")))


int main(int argc, char **argv) {
    return 0;
}