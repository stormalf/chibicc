#include <stdio.h>
#include <string.h>
#include "test.h"

struct MyStruct {
    void (*myFunc)(void *, const void *, size_t);
};

// Initialize the struct with memcpy assigned to the function pointer
struct MyStruct myStruct = {
    .myFunc = memcpy
};

int main() {
    // Use the function pointer
    char src[20] = "Hello, World!";
    char dest[20];
    myStruct.myFunc(dest, src, strlen(src));

    printf("Copied string: %s\n", dest);  // Should print: "Copied string: Hello, World!"
    ASSERT(0, !strncmp("Hello, World!", dest, strlen("Hello, World!")));

    return 0;
}
