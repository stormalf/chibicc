#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "memcached.h"
#define IOV_MAX 1024



int main() {
    int t1 = IOV_MAX - 1;
    int iovused = 10;
    int iovcnt = 10;
    bool resp = false;
    while (resp && iovused + iovcnt < IOV_MAX-1) {
      break;
    }
  printf("iovused %d iovcnt %d\n", iovused, iovcnt);
    return 0;
}