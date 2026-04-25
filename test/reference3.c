#include "test.h"
extern int ossl_fips_intern_provider_init(void);

int foo(void) {
    return 0 ? ossl_fips_intern_provider_init() : 1;
}

int main() {
    int x = foo();
    printf("%d\n", x);
    return 0;
}
