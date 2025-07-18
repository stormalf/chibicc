#include <uchar.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <linux/if_link.h>
#include <linux/types.h>
#include <stdio.h>
#include <asm/swab.h>
#include "test.h"
#include <linux/sched.h>

int main(){
    printf("sizeof struct clone_args=%ld\n", sizeof(struct clone_args));
    ASSERT(88, sizeof(struct clone_args));
    return 0;
}