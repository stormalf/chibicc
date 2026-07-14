#include "test.h"
#define ID(a, b) (a, b)
int f(void){ return ID((int[]){1, 2}, 3); }
int main(){ return f() - 3; }
