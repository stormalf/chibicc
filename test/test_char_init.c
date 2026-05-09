#include "test.h"
char c = -1;
int main() {
    printf("c = %d\n", c);
    ASSERT(-1, c);
    return 0;
}
