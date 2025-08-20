#include "vlc_common.h"
#include <stdio.h>

static
VLC_UNUSED_FUNC
VLC_WARN_CALL("thread name too big")
const char * vlc_thread_name_too_big( const char * thread_name )
{
    return thread_name;
}


int main(void)
{
    printf("ok\n");
    return 0;
}
