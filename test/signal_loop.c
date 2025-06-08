#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>
#include <signal.h>
#include <linux/types.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

/* Send signal SIG to the process PID.  Associate data in VAL with the
   signal.  */
extern int sigqueue (__pid_t __pid, int __sig, const union sigval __val)
     __THROW;


int main()
{
    printf("OK\n");
    return 0;
}