#include "test.h"
#include <stdlib.h>
#include <sys/wait.h> // For WEXITSTATUS and related macros

int main(void) {
    int ret = system("XXXX"); // Intentionally invalid command

    if (ret == -1) {
        perror("system");
        return 1;
    }

    // Check if the command terminated normally
    if (WIFEXITED(ret)) {
        int exit_status = WEXITSTATUS(ret);
        printf("Command exited with status: %d\n", exit_status);

        if (exit_status == 127)
            printf("As expected: command not found\n");
        else
            printf("Unexpected exit status\n");

        ASSERT(127, exit_status);
    } else {
        printf("Command did not exit normally\n");
    }
    
    return 0;
}
