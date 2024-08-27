#include <stdio.h>

typedef void* pg_stack_base_t;

pg_stack_base_t stack_base_ptr;

pg_stack_base_t set_stack_base(void)
{
#ifndef HAVE__BUILTIN_FRAME_ADDRESS
    char stack_base;
#endif
    pg_stack_base_t old;

    old = stack_base_ptr;

    /*
     * Set up reference point for stack depth checking. On recent gcc we use
     * __builtin_frame_address() to avoid a warning about storing a local
     * variable's address in a long-lived variable.
     */
#ifdef HAVE__BUILTIN_FRAME_ADDRESS
    stack_base_ptr = __builtin_frame_address(0);
#else
    stack_base_ptr = &stack_base;
#endif

    return old;
}

int main(void)
{
    pg_stack_base_t old_base = set_stack_base();
    printf("Old stack base: %p\n", old_base);
    printf("Current stack base: %p\n", stack_base_ptr);
    return 0;
}
