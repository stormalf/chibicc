#include "test.h"
char sc1 = "foobar"[4];
int main() {
    // If it's a char, why is the assembly '.quad .L..9+4'?
    // That's 8 bytes. A char should be '.byte 97'.
    return 0;
}
