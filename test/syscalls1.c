
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/mman.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include "test.h"


int main() {
    // Write to standard output
    const char *msg = "Hello, world!\n";
    syscall(SYS_write, STDOUT_FILENO, msg, 14);

    // Read from standard input
    // char buffer[128];
    // ssize_t bytesRead = syscall(SYS_read, STDIN_FILENO, buffer, sizeof(buffer) - 1);
    // if (bytesRead >= 0) {
    //     buffer[bytesRead] = '\0';
    //     printf("Read: %s\n", buffer);
    // }

    // Open a file and read from it
    int fd = syscall(SYS_open, "test.txt", O_RDONLY);
    if (fd >= 0) {
        char buffer[128];
        ssize_t bytesRead = syscall(SYS_read, fd, buffer, sizeof(buffer) - 1);
        if (bytesRead >= 0) {
            buffer[bytesRead] = '\0';
            printf("Read from file: %s\n", buffer);
        }
        syscall(SYS_close, fd);
    }

    // Get the process ID
    pid_t pid = syscall(SYS_getpid);
    printf("Process ID: %d\n", pid);

    // Fork a child process
    pid = syscall(SYS_fork);
    if (pid == 0) {
        printf("This is the child process\n");
    } else if (pid > 0) {
        printf("This is the parent process, child PID: %d\n", pid);
    } else {
        printf("Fork failed\n");
    }

    //Execute a program
    // char *argv[] = { "/bin/ls", "-l", NULL };
    // char *envp[] = { NULL };
    // syscall(SYS_execve, "/bin/ls", argv, envp);

    // Map a file into memory
    fd = syscall(SYS_open, "test.txt", O_RDONLY);
    if (fd >= 0) {
        char *data = syscall(SYS_mmap, NULL, 4096, PROT_READ, MAP_PRIVATE, fd, 0);
        if (data != MAP_FAILED) {
            printf("Mapped data: %s\n", data);
            syscall(SYS_munmap, data, 4096);
        }
        syscall(SYS_close, fd);
    }


    // Kill a process
    // pid = syscall(SYS_getpid);
    // syscall(SYS_kill, pid, SIGTERM);

    // Get the current time
    struct timeval tv;
    syscall(SYS_gettimeofday, &tv, NULL);
    printf("Seconds: %ld\nMicroseconds: %ld\n", tv.tv_sec, tv.tv_usec);

    // Get system information
    struct utsname bufferinfo;
    if (syscall(SYS_uname, &bufferinfo) == 0) {
        printf("System name: %s\n", bufferinfo.sysname);
        printf("Node name: %s\n", bufferinfo.nodename);
        printf("Release: %s\n", bufferinfo.release);
        printf("Version: %s\n", bufferinfo.version);
        printf("Machine: %s\n", bufferinfo.machine);
        Assert("x86_64", bufferinfo.machine);
        Assert("Linux", bufferinfo.sysname);
    } else {
        perror("syscall(SYS_uname) failed");
    }

    // Get the current user and group IDs
    uid_t uid = syscall(SYS_getuid);
    printf("User ID: %d\n", uid);
    gid_t gid = syscall(SYS_getgid);
    printf("Group ID: %d\n", gid);

    // Exit the process
    syscall(SYS_exit, 0);
}
