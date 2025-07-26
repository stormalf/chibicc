#include <sys/sem.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include "test.h"

/*
 * Note: On modern Linux, `union semun` is typically not declared in headers
 * due to historical POSIX issues, so we declare it ourselves.
 */
union semun {
  int val;
  struct semid_ds *buf;
  unsigned short *array;
  struct seminfo *__buf;
};

int main() {
  struct seminfo seminfo;
  union semun arg;
  printf("sizeof(struct seminfo) = %zu\n", sizeof(struct seminfo));
  ASSERT(40, sizeof(struct seminfo));
  arg.__buf = &seminfo; // For SEM_INFO, .__buf should point to seminfo

  int ret = semctl(0, 0, SEM_INFO, arg);

  if (ret < 0) {
    printf("semctl SEM_INFO failed: %s\n", strerror(errno));
    return 1;
  }

  printf("semctl SEM_INFO succeeded\n");
  printf("seminfo.semusz (used arrays): %d\n", seminfo.semusz);
  ASSERT(0, seminfo.semusz);
  printf("seminfo.semaem (allocated semaphores): %d\n", seminfo.semaem);
  ASSERT(0, seminfo.semaem); 

  return 0;
}
