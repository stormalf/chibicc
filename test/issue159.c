
#include <stdbool.h>
#include <stddef.h>
#include "test.h"
// represents a variable
union Var {
  float f;
  char *s;
  bool b;
  // 'f' 's' or 'b'
  char type;
};

// #define foo(x)                                                    \
//   __builtin_choose_expr (                                         \
//     __builtin_types_compatible_p (typeof (x), double),            \
//     foo_double (x),                                               \
//     __builtin_choose_expr (                                       \
//       __builtin_types_compatible_p (typeof (x), float),           \
//       foo_float (x),                                              \
//       /* The void expression results in a compile-time error  \
//          when assigning the result to something.  */          \
//       (void)0))


#define ts_subtree_children(self) \
  ((self) ? NULL : (union Var *)((self)))

// // setter
void set_int(union Var *var, int newval) { var->f = (float)newval; var->type = 'f'; }
void set_float(union Var *var, float newval) { var->f = newval; var->type = 'f';  printf("var->f=%f\n", var->f); ASSERT(1, var->f);}
void set_char(union Var *var, char newval) { var->s = (char[2]){newval, 0}; var->type = 's'; }
void set_string(union Var *var, char *newval) { var->s = newval; var->type = 's'; }
void set_bool(union Var *var, bool newval) { var->b = newval; var->type = 'b'; }
#define set(VAR, X) \
  _Generic((X), \
    int: set_int, \
    float: set_float, \
    double: set_float, \
    char: set_char, \
    char *: set_string, \
    bool: set_bool)((VAR), (X))

int main(void) {
    union Var myvar;

    
    set(&myvar, 1.5);
    char c = 'c';
    char *pc = &c;
    int i = 0;
    union Var *tsubtree[1];
    const union Var *child = &ts_subtree_children(tsubtree)[i];
    ASSERT(NULL, child);
    printf("child is null! = %p\n", child);
    return 0;
}