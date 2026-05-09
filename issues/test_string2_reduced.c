#include "test.h"
int main() {
    static char sc1 = "foobar"[4];
    printf("sc1 = %d ('%c')\n", sc1, sc1);
    ASSERT('a', sc1);
    return 0;
}
