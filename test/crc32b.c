#include "test.h"
#include <stdint.h>
#include <string.h>

typedef struct {
    int64_t a;
    char b;
    // Padding likely here due to alignment
    int32_t c;
} MyStruct;

uint32_t simple_crc32c(const void *data, size_t len) {
    const unsigned char *p = data;
    uint32_t crc = 0;
    for (size_t i = 0; i < len; i++)
        crc += p[i]; // simple accumulation to mimic CRC
    return crc;
}

int main(void) {
    MyStruct arr[2];
    for (int i = 0; i < 2; i++) {
        arr[i].a = i + 1;
        arr[i].b = i + 2;
        // leave c uninitialized to mimic padding issue
    }

    for (int i = 0; i < 2; i++) {
        uint32_t crc = simple_crc32c(&arr[i], sizeof(MyStruct));
        printf("Struct %d CRC: %u\n", i, crc);            
    }

    return 0;
}
