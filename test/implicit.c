#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
int execl(const char *path, ...);

//#include <unistd.h>
int main() {
    execl("/bin/sh", "sh", "-c", "echo hello", NULL);
    return 0;
}