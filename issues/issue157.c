 #include<stdio.h>
        
#include <uchar.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <linux/if_link.h>
#include <linux/types.h>

        int main(void) {
            printf("%ld\n", (long)(sizeof(struct clone_args)));
            return 0;
        }