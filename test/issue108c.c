#include <stdio.h>


# if __has_attribute(noinline)
#  define VLC_NOINLINE_FUNC  __attribute__((noinline))
# else
#  define VLC_NOINLINE_FUNC
# endif



#define VLC_UNUSED_FUNC __attribute__((unused))
#define VLC_WARN_CALL(w) VLC_NOINLINE_FUNC __attribute__((warning((w))))

static
VLC_UNUSED_FUNC
VLC_WARN_CALL("thread name too big")
const char * vlc_thread_name_too_big( const char * thread_name )
{
    return thread_name;
}

int main(void) {
    printf("ok\n");
    return 0;
}