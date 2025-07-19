#include "test.h"

// Define the original function `lxc_attach_main`.
int lxc_attach_main(int argc, char *argv[]) {
    printf("This is lxc_attach_main.\n");
    return 0;
}

// Declare `main` as a weak alias of `lxc_attach_main`.
int __attribute__((weak, alias("lxc_attach_main"))) main(int argc, char *argv[]);
