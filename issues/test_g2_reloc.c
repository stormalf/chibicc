#include "test.h"

const int arr[2][2] = {{1,2},{3,4}};
int g1 = ((int){77});
int g2 = arr[1][1];

int main() {
    printf("g1 = %d\n", g1);
    printf("g2 = %d\n", g2);
    ASSERT(77, g1);
    ASSERT(4, g2);
    return 0;
}
