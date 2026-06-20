// Test select() timeout behavior
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>

int main() {
  struct timeval tv;
  fd_set rfds;
  int ret;

  FD_ZERO(&rfds);
  tv.tv_sec = 0;
  tv.tv_usec = 10000; // 10ms

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  ret = select(1, &rfds, NULL, NULL, &tv);

  clock_gettime(CLOCK_MONOTONIC, &end);
  double elapsed = (end.tv_sec - start.tv_sec) * 1000.0 +
                   (end.tv_nsec - start.tv_nsec) / 1000000.0;

  printf("select returned: %d (expected 0 for timeout)\n", ret);
  printf("elapsed: %.3f ms (expected ~10ms)\n", elapsed);

  if (elapsed > 5.0 && elapsed < 50.0)
    printf("PASS: timeout behavior correct\n");
  else
    printf("FAIL: unexpected timeout\n");

  // Test struct timeval layout
  printf("\nsizeof(struct timeval) = %zu\n", sizeof(struct timeval));
  printf("sizeof(time_t) = %zu\n", sizeof(time_t));
  printf("sizeof(suseconds_t) = %zu\n", sizeof(suseconds_t));
  printf("offsetof tv_sec = %zu\n", (size_t)&((struct timeval*)0)->tv_sec);
  printf("offsetof tv_usec = %zu\n", (size_t)&((struct timeval*)0)->tv_usec);

  return ret == 0 ? 0 : 1;
}
