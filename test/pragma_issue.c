
#include <stdio.h>

#define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                \
                _Pragma ("GCC diagnostic push")             \
                _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"") \
                 _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")

# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")

int main() {
    YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN;
    //test
    YY_IGNORE_MAYBE_UNINITIALIZED_END;
    printf("OK\n");
    return 0;
}