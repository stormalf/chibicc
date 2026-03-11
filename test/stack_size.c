#include <stdio.h>
#include <stdint.h>

__attribute__((noinline))
void recursive(int depth, char **base) {
    volatile char local;

    // Capture the deepest stack address (first call)
    if (depth == 0)
        *base = (char *)&local;

    // Prevent tail-call elimination
    if (depth < 100000) {
        recursive(depth + 1, base);       
    } else {
        char *end = (char *)&local;
        long total = *base - end;

        printf("Stack usage for %d calls: %ld bytes\n", depth, total);
        printf("Average stack usage per call: %.2f bytes\n",
               (double)total / depth);
    }
}

int main(void) {
    char *base = 0;
    recursive(0, &base);
    return 0;
}
