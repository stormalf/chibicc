#include <stdio.h>
struct Point {
    int x;
    int y;
};

int main() {
    struct Point pt = {3, 4};
    printf("Point(%d, %d)\n", pt.x, pt.y);
    return 0;
}