// Reproducer for a PostgreSQL-like "pid field reads wrong value" failure mode.
//
// This focuses on struct member layout drift: if member offsets diverge from
// the ABI layout, reading `pid` from shared memory can fetch unrelated data.

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct ProcLike {
  int head;
  int pgprocno __attribute__((aligned(64)));
  int pid;
  int tail;
};

int main(void) {
  size_t off_pgprocno = offsetof(struct ProcLike, pgprocno);
  size_t off_pid = offsetof(struct ProcLike, pid);

  printf("offsetof(pgprocno)=%zu\n", off_pgprocno);
  printf("offsetof(pid)=%zu\n", off_pid);
  printf("sizeof(ProcLike)=%zu align=%zu\n", sizeof(struct ProcLike), _Alignof(struct ProcLike));

  // GCC x86_64 SysV layout for this shape:
  //   pgprocno @ 64, pid @ 68
  // Chibicc currently computes pid @ 128 on this tree.
  if (off_pgprocno != 64 || off_pid != 68) {
    printf("LAYOUT_MISMATCH: expected pgprocno=64 pid=68\n");
  }

  _Alignas(64) unsigned char raw[256] = {0};

  *(int *)(raw + 64) = 25;         // e.g. slot index / pgprocno
  *(int *)(raw + 68) = (int)getpid(); // expected pid location in ABI layout

  struct ProcLike *p = (struct ProcLike *)raw;

  printf("raw[64]=%d raw[68]=%d\n", *(int *)(raw + 64), *(int *)(raw + 68));
  printf("p->pgprocno=%d p->pid=%d getpid()=%d\n", p->pgprocno, p->pid, (int)getpid());

  if (p->pid != (int)getpid()) {
    printf("REPRODUCED: pid field read does not match getpid()\n");
    return 1;
  }

  printf("OK\n");
  return 0;
}
