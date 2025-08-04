#include "test.h"
#include <stdlib.h>
#include <sys/io.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  if (geteuid() != 0) {
    printf("Must be run as root.\n");
    return 0;
  }

  // Request access to port 0x60 (keyboard controller)
  if (ioperm(0x60, 1, 1)) {
    printf("ioperm failed\n");
    return 0;
  }

  unsigned char val = inb(0x60);
  printf("Read value: 0x%02x from port 0x60\n", val);

  // Revoke access
  ioperm(0x60, 1, 0);

  return 0;
}