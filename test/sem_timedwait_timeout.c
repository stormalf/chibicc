#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include "test.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static sem_t sema;

static void *late_post(void *arg) {
  (void)arg;
  usleep(2000 * 1000); // 2s
  sem_post(&sema);
  return NULL;
}

int main(void) {
  if (sem_init(&sema, 0, 0) != 0) {
    perror("sem_init");
    return 1;
  }

  // Capture the clock *before* spawning the poster so the deadline and the
  // poster's sleep are measured from the same origin.  Otherwise, under
  // system overload the main thread may be descheduled between
  // pthread_create() and gettimeofday(), pushing the deadline past the
  // poster's post and making sem_timedwait() succeed instead of timing out.
  struct timeval now;
  if (gettimeofday(&now, NULL) != 0) {
    perror("gettimeofday");
    return 1;
  }

  pthread_t th;
  if (pthread_create(&th, NULL, late_post, NULL) != 0) {
    perror("pthread_create");
    return 1;
  }

  // Mirror CPython _multiprocessing/semaphore.c deadline math.
  double timeout = 0.5; // 500ms
  long sec = (long)timeout;
  long nsec = (long)(1e9 * (timeout - sec) + 0.5);

  struct timespec deadline;
  deadline.tv_sec = now.tv_sec + sec;
  deadline.tv_nsec = now.tv_usec * 1000 + nsec;
  deadline.tv_sec += (deadline.tv_nsec / 1000000000);
  deadline.tv_nsec %= 1000000000;

  errno = 0;
  int rc = sem_timedwait(&sema, &deadline);
  int err = errno;

  pthread_join(th, NULL);
  sem_destroy(&sema);

  if (rc == 0) {
    // This means timeout was effectively ignored: bug scenario.
    printf("FAIL: sem_timedwait succeeded (should timeout)\n");
    return 1;
  }

  if (err != ETIMEDOUT) {
    printf("FAIL: sem_timedwait errno=%d expected=%d\n", err, ETIMEDOUT);
    return 1;
  }

  printf("OK\n");
  return 0;
}
