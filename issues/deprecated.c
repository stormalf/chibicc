//#include <systemd/_sd-common.h>


#include <stdio.h>
#ifndef _sd_deprecated_
#  if __GNUC__ >= 6
#    define _sd_deprecated_ __attribute__((__deprecated__))
#  else
#    define _sd_deprecated_
#  endif
#endif

_sd_deprecated_
void old_function() {
    printf("This function is deprecated.\n");
}

int main() {
    old_function();
    return 0;
}
