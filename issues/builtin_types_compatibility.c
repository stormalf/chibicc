#include <stdio.h>
int main() {
    if (__builtin_types_compatible_p(int, int)) {
        printf("Types are compatible\n");
    } else {
        printf("Types are not compatible\n");
    }
    return 0;
}

