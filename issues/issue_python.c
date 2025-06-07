#include <stdio.h>

struct Outer {
    int x;
struct {
        /* Has been initialized to a safe state.

           In order to be effective, this must be set to 0 during or right
           after allocation. */
        unsigned int initialized:1;

        /* Has been bound to an OS thread. */
        unsigned int bound:1;
        /* Has been unbound from its OS thread. */
        unsigned int unbound:1;
        /* Has been bound aa current for the GILState API. */
        unsigned int bound_gilstate:1;
        /* Currently in use (maybe holds the GIL). */
        unsigned int active:1;

        /* various stages of finalization */
        unsigned int finalizing:1;
        unsigned int cleared:1;
        unsigned int finalized:1;

        /* padding to align to 4 bytes */
        unsigned int :24;
    } status;
};

int main() {
    struct Outer t = {0};
    
    printf("Before: initialized = %u, bound = %u\n", t.status.initialized, t.status.bound);

    t.status.initialized = 1;
    t.status.bound = 1;

    printf("After: initialized = %u, bound = %u\n", t.status.initialized, t.status.bound);

    if (t.status.initialized) {
        puts("Thread state is initialized.");
    } else {
        puts("Thread state is NOT initialized.");
    }

    return 0;
}
