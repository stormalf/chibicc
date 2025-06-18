//#include "sd-id128.h"
#include <inttypes.h>
#include <stdarg.h>
#include <string.h>

typedef union sd_id128 sd_id128_t;

union sd_id128 {
        uint8_t bytes[16];
        uint64_t qwords[2];
};

int sd_id128_in_setv2(sd_id128_t a, va_list ap) {
        for (;;) {
                sd_id128_t b = va_arg(ap, sd_id128_t);
                 
        }
        return 0;
}

int main() {
    return 0;
}