#include <stdlib.h>
#include "test.h"

int main() {
  FILE *fp = popen("XXXX", "r");
  if (fp == NULL) {
    perror("popen");
    return 1;
  }
  char buf[128];
  while (fgets(buf, sizeof(buf), fp)) {
    printf("Output: %s", buf);
  }
  int status = pclose(fp);
  printf("Status: %d\n", status);
  ASSERT(32512, status);
  return 0;
}
