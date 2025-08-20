// test_weak_array.c
#include "test.h"

typedef void (*plugin_cb)(void);

// extern declaration, mimicking VLC's vlc_static_modules array
extern plugin_cb vlc_static_modules[];

void use_plugins(void) {
    if (vlc_static_modules) {
        printf("vlc_static_modules is defined!\n");
    } else {
        printf("vlc_static_modules is NULL or empty\n");
    }
}

int main(void) {
    use_plugins();
    return 0;
}
