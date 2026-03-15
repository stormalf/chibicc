#include "test.h"

char sc1 = "foobar"[4];

int main() {
    printf("sc1 = %d ('%c')\n", sc1, sc1);
    if (sc1 == 'a') {
        printf("OK\n");
    } else {
        printf("FAIL: expected 'a' (97), but got %d\n", sc1);
        return 1;
    }
    return 0;
}
