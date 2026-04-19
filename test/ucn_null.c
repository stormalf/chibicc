#include "test.h"
#include <string.h>

int main() {
    char *s = "x\u0000y";
    if (s[0] == 'x' && s[1] == '\0' && s[2] == 'y') {
        printf("OK\n");
        return 0;
    }
    return 1;
}