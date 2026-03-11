#include <stdio.h>
#include <stddef.h>

struct ProcLike {
  int head;
  int pgprocno __attribute__((aligned(64)));
  int pid;
  int tail;
};

int main() {
    printf("offsetof(head) = %zu\n", offsetof(struct ProcLike, head));
    printf("offsetof(pgprocno) = %zu\n", offsetof(struct ProcLike, pgprocno));
    printf("offsetof(pid) = %zu\n", offsetof(struct ProcLike, pid));
    printf("offsetof(tail) = %zu\n", offsetof(struct ProcLike, tail));

    if (offsetof(struct ProcLike, pgprocno) != 64) {
        printf("BUG: pgprocno offset is %zu, expected 64\n", offsetof(struct ProcLike, pgprocno));
        return 1;
    }
    if (offsetof(struct ProcLike, pid) != 68) {
        printf("BUG: pid offset is %zu, expected 68\n", offsetof(struct ProcLike, pid));
        return 1;
    }
    printf("OK\n");
    return 0;
}
