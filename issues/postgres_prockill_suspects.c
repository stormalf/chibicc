#include "test.h"

#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

typedef unsigned long Datum;
typedef void (*pg_on_exit_callback)(int code, Datum arg);

struct on_proc_exit_item {
  pg_on_exit_callback function;
  Datum arg;
};

static struct on_proc_exit_item on_proc_exit_list[16];
static int on_proc_exit_count;

static pid_t MyProcPid;
static volatile int ProcKillCalls;
static volatile int GuardWordA;
static volatile int GuardWordB;

static void reset_state(void) {
  on_proc_exit_count = 0;
  ProcKillCalls = 0;
  MyProcPid = getpid();
  GuardWordA = 0x13579BDF;
  GuardWordB = 0x2468ACE0;
}

static void on_proc_exit(pg_on_exit_callback function, Datum arg) {
  on_proc_exit_list[on_proc_exit_count].function = function;
  on_proc_exit_list[on_proc_exit_count].arg = arg;
  on_proc_exit_count++;
}

static void shmem_exit(int code) {
  for (int i = on_proc_exit_count - 1; i >= 0; i--)
    on_proc_exit_list[i].function(code, on_proc_exit_list[i].arg);
}

static void ProcKill(int code, Datum arg) {
  (void)code;
  (void)arg;
  ProcKillCalls++;

  if (getpid() != MyProcPid) {
    /* Mirrors PostgreSQL PANIC path: ProcKill in child should abort. */
    abort();
  }
}

static void GuardCallback(int code, Datum arg) {
  (void)code;
  ASSERT(0xAAAA5555, (int)arg);
  ASSERT(0x13579BDF, (int)GuardWordA);
  ASSERT(0x2468ACE0, (int)GuardWordB);
}

static void test_child_running_proc_exit_panics(void) {
  reset_state();
  on_proc_exit(ProcKill, 0);

  pid_t pid = fork();
  if (pid == 0) {
    shmem_exit(0);
    _exit(0);
  }

  int status = 0;
  waitpid(pid, &status, 0);
  ASSERT(1, WIFSIGNALED(status));
  ASSERT(SIGABRT, WTERMSIG(status));
}

static void test_child_using__exit_avoids_panic(void) {
  reset_state();
  on_proc_exit(ProcKill, 0);

  pid_t pid = fork();
  if (pid == 0)
    _exit(0);

  int status = 0;
  waitpid(pid, &status, 0);
  ASSERT(1, WIFEXITED(status));
  ASSERT(0, WEXITSTATUS(status));
}

static void test_callback_integrity_in_parent(void) {
  reset_state();
  on_proc_exit(ProcKill, 0);
  on_proc_exit(GuardCallback, 0xAAAA5555UL);

  shmem_exit(0);
  ASSERT(1, (int)ProcKillCalls);
  ASSERT(0x13579BDF, (int)GuardWordA);
  ASSERT(0x2468ACE0, (int)GuardWordB);
}

static void test_child_bounded_loop_finishes(void) {
  pid_t pid = fork();
  if (pid == 0) {
    volatile int x = 0;
    for (int i = 0; i < 2000000; i++)
      x += (i & 1);

    if (x == 1000000)
      _exit(0);
    _exit(2);
  }

  int status = 0;
  waitpid(pid, &status, 0);
  ASSERT(1, WIFEXITED(status));
  ASSERT(0, WEXITSTATUS(status));
}

int main(void) {
  test_child_running_proc_exit_panics();
  test_child_using__exit_avoids_panic();
  test_callback_integrity_in_parent();
  test_child_bounded_loop_finishes();
  printf("OK\n");
  return 0;
}
