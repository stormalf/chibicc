#include <stdio.h>
int main() {
    char src[] = "Hello, world!";
    char dest[20];
    __builtin_memcpy(dest, src, sizeof(src));
    printf("Copied string: %s\n", dest);
    return 0;
}

