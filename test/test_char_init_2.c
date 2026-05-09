#include "test.h"
char c = 255;
int main() {
    printf("c = %d\n", c);
    ASSERT(-1, c);
    return 0;
}
