#include "test.h"

int main() {
    int x = 1;
    int result = 0;
    switch (x) {
    case 1:
        result = 10;
        break;
        ;
    case 2:
        result = 20;
        break;
    }
    printf("%d\n", result);
    return 0;
}
