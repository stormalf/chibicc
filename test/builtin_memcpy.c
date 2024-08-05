#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "Hello, world!";
    char dest[20];
    memcpy(dest, src, sizeof(src)); // Use memcpy instead of __builtin_memcpy
    printf("Copied string: %s\n", dest);
    return 0;
}
