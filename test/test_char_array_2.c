#include "test.h"
int main() {
    char c = "foobar"[4];
    printf("c = %d ('%c')\n", c, c);
    ASSERT('a', c);
    return 0;
}
