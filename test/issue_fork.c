#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

__thread int tls_counter = 7;

void *thread_func(void *arg) {
    tls_counter++;
    return NULL;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, thread_func, NULL);
    pthread_join(t, NULL);

    printf("Before fork: pid=%d, tls=%d\n", getpid(), tls_counter);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child: pid=%d, tls=%d\n", getpid(), tls_counter);
        exit(0);
    } else {
        wait(NULL);
        printf("Parent: pid=%d, tls=%d\n", getpid(), tls_counter);
    }

    return 0;
}
