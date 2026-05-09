#include "test.h"
char sc1 = "foobar"[4];
int main() {
    printf("sc1 = %d ('%c')\n", sc1, sc1);
    ASSERT('a', sc1);
    return 0;
}
