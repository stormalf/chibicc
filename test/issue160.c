#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "memcached.h"
#include <assert.h>



int main() {
    int t1 = IOV_MAX - 1;
    int iovused = 10;
    int iovcnt = 10;
    bool resp = false;
    while (resp && iovused + iovcnt < IOV_MAX-1) {
      break;
    }

    printf("t1=%d iovused=%d iovcnt=%d\n", t1, iovused, iovcnt);
    assert(1023 == t1);
    assert(10 == iovused);
    assert(10 == iovcnt);
    return 0;
}