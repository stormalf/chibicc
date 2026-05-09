#include "test.h"
char sc1 = "foobar"[4];
char sc2 = "foobar"[1];
int main() {
    printf("sc1 = %d ('%c')\n", sc1, sc1);
    printf("sc2 = %d ('%c')\n", sc2, sc2);
    ASSERT('a', sc1);
    ASSERT('o', sc2);
    printf("OK\n");
    return 0;
}
