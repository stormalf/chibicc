#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include <omp.h>

typedef __UINTPTR_TYPE__ omp_uintptr_t;

int main(int argc, char **argv) {
    int num_threads,tid;
#pragma omp parallel //parallel execution begin

    {
        tid = omp_get_thread_num();
        printf("Thread id: %d\n", tid);
        if (tid == 0)
        {
            num_threads = omp_get_num_threads();
            printf("Number of threads: %d\n", num_threads);
        }
    }
    return 0;

}