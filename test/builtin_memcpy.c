
#include <string.h>
#include "test.h"

int main() {
    char src[] = "Hello, world!";
    char dest[20];
    memcpy(dest, src, strlen(src)); // Use memcpy instead of __builtin_memcpy
    printf("Copied string: %s\n", dest);
    ASSERT(0, !strcmp(dest, "Hello, world!"));
    return 0;
}
