#include <stdio.h>

// Simulate what VLC does
#if __has_attribute(warning)
#  define VLC_WARN_CALL(w) __attribute__((warning(w))) __attribute__((noinline))
#else
#  define VLC_WARN_CALL(w)
#endif


VLC_WARN_CALL("thread name too big")
const char * vlc_thread_name_too_big( const char * thread_name )
{
    return thread_name;
}

// Declare a function that should trigger a compiler warning if supported
int deprecated_function(void) VLC_WARN_CALL("deprecated_function() is unsafe, don't use it");
int deprecated_function(void) {
    return 42;
}

VLC_WARN_CALL("thread name too big") int foo() {
    return 0;
}

int main(void) {    
    int x = deprecated_function(); // Should emit warning if supported
    printf("Value = %d\n", x);
    return 0;
}
