#include "test.h"
static inline void fn(void);
void (*ptr)(void) = fn;
int main(void) {
    ptr();
    return 0;
}
static inline void fn(void) {}