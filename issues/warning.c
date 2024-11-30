#include <stdio.h>

// Define the VLC_WARN_CALL macro with a custom warning attribute
#define VLC_UNUSED_FUNC  __attribute__((unused))
#define VLC_NOINLINE_FUNC __attribute__((noinline))
#define VLC_WARN_CALL(w)  VLC_NOINLINE_FUNC __attribute__((warning((w))))


#if defined(__GNUC__)
static
VLC_UNUSED_FUNC
VLC_WARN_CALL("thread name too big")
const char * vlc_thread_name_too_big( const char * thread_name )
{
    return thread_name;
}

# define check_name_length( thread_name ) \
    ((__builtin_constant_p(__builtin_strlen(thread_name) > 15) && \
      __builtin_strlen(thread_name) > 15) \
      ? vlc_thread_name_too_big(thread_name): thread_name)
#endif

// Use VLC_WARN_CALL to mark this function as deprecated with a custom warning message
VLC_WARN_CALL("This function is deprecated, use `new_function` instead.")
void deprecated_function() {
    printf("Deprecated function called.\n");
}

// A replacement function without any warnings
void new_function() {
    printf("New function called.\n");
}

int main() {
    deprecated_function();  // This will trigger the warning
    new_function();         // This will not trigger any warnings
    return 0;
}
