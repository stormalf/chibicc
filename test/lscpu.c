
#include <stdarg.h>
#include "test.h"

void test_variadic(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);

    // Assume you expect two ints: cores_per_socket and sockets
    int cores_per_socket = va_arg(ap, int);
    ASSERT(2, cores_per_socket);
    int sockets = va_arg(ap, int);
    ASSERT(1, sockets);

    va_end(ap);

    printf("Read cores_per_socket = %d\n", cores_per_socket);
    printf("Read sockets = %d\n", sockets);
}

int main() {
    int cores = 2;
    int sockets = 1;

    printf("Passing cores=%d, sockets=%d\n", cores, sockets);
    test_variadic("%d%d", cores, sockets);

    return 0;
}
