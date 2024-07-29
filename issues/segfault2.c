#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/resource.h>

void enable_core_dump() {
    struct rlimit rl;
    rl.rlim_cur = RLIM_INFINITY;
    rl.rlim_max = RLIM_INFINITY;
    if (setrlimit(RLIMIT_CORE, &rl) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }
}

void segfault_handler(int signum) {
    printf("Segmentation fault (signal %d)\n", signum);
    abort();  // Generate a core dump
}

void setup_signal_handlers() {
    signal(SIGSEGV, segfault_handler);
}

int main() {
    enable_core_dump();
    setup_signal_handlers();

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP);
        // Child process code
        char *path = "~/postgres/tmp_install/usr/local/pgsql/bin:~/postgres:$PATH";
        char *ld_library_path = "~/postgres/tmp_install/usr/local/pgsql/lib:$LD_LIBRARY_PATH";
        char *initdb_template = "~/postgres/tmp_install/initdb-template";
        char *argv[] = {
            "initdb",
            "-A", "trust",
            "-N",
            "--no-instructions",
            "--no-locale",
            initdb_template,
            NULL
        };
        char *envp[] = {
            path,
            ld_library_path,
            NULL
        };

        execvp(argv[0], argv);
        perror("execvp");  // execvp only returns on error
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, NULL, 0);  // Wait for the child process to stop
        char cmd[256];
        snprintf(cmd, sizeof(cmd), "gdb -p %d -ex 'set pagination off'-ex 'set confirm off' -ex 'continue' -ex 'detach' -ex 'quit'", pid);
        system(cmd);
        ptrace(PTRACE_CONT, pid, NULL, NULL);  // Continue the child process
    }

    return 0;
}
