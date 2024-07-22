#include <sys/types.h>
#include <sys/time.h>

#include <signal.h>
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdint.h>



int main(void) {
    printf("%d", (int) sizeof(int));
    return 0;
}