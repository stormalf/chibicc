// weak2.c
#include <stdio.h>

typedef void (*vlc_plugin_cb)(void);

// Simulate VLC_WEAK macro
#define VLC_WEAK __attribute__((weak))

// Weak symbol declaration
VLC_WEAK
extern const vlc_plugin_cb vlc_static_modules[];

// Function using the weak symbol
void init_plugins(void) {
    // if (!vlc_static_modules) {
    //     printf("vlc_static_modules not defined\n");
    //     return;
    // }

    // for (unsigned i = 0; vlc_static_modules[i]; i++) {
    //     printf("Plugin %u initialized\n", i);
    //     vlc_static_modules[i]();
    //}
}

// Dummy plugin
void plugin1(void) {
    printf("Plugin1 executed\n");
}

// Uncomment to define the weak array for testing
// const vlc_plugin_cb vlc_static_modules[] = { plugin1, NULL };
