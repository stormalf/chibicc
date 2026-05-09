// test3.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// external function (not defined in this TU)
void extfn(void) {
    return;
}

static inline void playlist_bookmark_Set(const char *name) {
    extfn();  // reference to an external symbol
}

static inline void playlist_bookmark_Play(const char *name) {
    puts(name); // reference to libc
}

// simulate VLC macro calling inline functions
#define INTF_ACTION_HANDLER(name) \
    void action_handler_##name(int action_id) { \
        char bookmark_name[32]; \
        snprintf(bookmark_name, sizeof(bookmark_name), "bookmark%i", action_id); \
        if (action_id % 2) \
            playlist_bookmark_Set(bookmark_name); \
        else \
            playlist_bookmark_Play(bookmark_name); \
    }

// instantiate the macro
INTF_ACTION_HANDLER(PlaylistBookmark)

int main(void) {
   // action_handler_PlaylistBookmark(1);
    //action_handler_PlaylistBookmark(2);
    return 0;
}
