#include "test.h"

#define IS_ATOMIC_INT(v) _Generic(&(v), _Atomic int *: 1, default: 0)
#define IS_CONST_INT(v) _Generic(&(v), const int *: 1, default: 0)
#define IS_VOLATILE_INT(v) _Generic(&(v), volatile int *: 1, default: 0)
#define IS_RESTRICT_TYPE(expr) \
  _Generic((expr), int * restrict: 1, default: 0)
#define IS_RESTRICT_PTR(v) _Generic(&(v), int * restrict *: 1, default: 0)

_Atomic int a;
int c;
const int d = 10;
volatile int e;
int * restrict p;

int main()
{ 
    /* Test that atomic variables remain atomic */
    ASSERT(1, IS_ATOMIC_INT(a));
    ASSERT(0, IS_ATOMIC_INT(c));
    
    /* Test that const variables are correctly marked */
    ASSERT(1, IS_CONST_INT(d));
    ASSERT(0, IS_CONST_INT(c));
    
    /* Test that volatile variables are correctly marked */
    ASSERT(1, IS_VOLATILE_INT(e));
    ASSERT(0, IS_VOLATILE_INT(c));
    
    /* Test that restrict pointers are correctly marked */
    ASSERT(0, IS_RESTRICT_TYPE(p));
    ASSERT(0, IS_RESTRICT_TYPE(&c));
    ASSERT(1, IS_RESTRICT_PTR(p));
    
    /* Test that operations work correctly on both */
    a+=1; 
    c+=1;
    e+=1;
    
    return 0; 
}
