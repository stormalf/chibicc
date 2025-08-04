#define _GNU_SOURCE
#include "test.h"
#include <uuid/uuid.h>
#include <sys/time.h>
#include <stdint.h>

typedef unsigned char uuid_t[16];  // If <uuid/uuid.h> is not found

struct uuid {
    uint32_t time_low;
    uint16_t time_mid;
    uint16_t time_hi_and_version;
    uint8_t  clock_seq_hi_and_reserved;
    uint8_t  clock_seq_low;
    uint8_t  node[6];
};



// Weak alias
extern time_t uuid_time(const uuid_t uu, struct timeval *ret_tv)
    __attribute__((weak, alias("__uuid_time")));

    
// Simulate the type decoder
int __uuid_type(const struct uuid *uu) {
    return (uu->time_hi_and_version >> 12);
}

#define UUID_TYPE_DCE_TIME     1
#define UUID_TYPE_DCE_TIME_V6  6
#define UUID_TYPE_DCE_TIME_V7  7

void uuid_unpack(const uuid_t in, struct uuid *uu) {
    // Very naive unpacking; only for test/demo purposes
    uu->time_low = (in[0] << 24) | (in[1] << 16) | (in[2] << 8) | in[3];
    uu->time_mid = (in[4] << 8) | in[5];
    uu->time_hi_and_version = (in[6] << 8) | in[7];
    uu->clock_seq_hi_and_reserved = in[8];
    uu->clock_seq_low = in[9];
    for (int i = 0; i < 6; i++) {
        uu->node[i] = in[10 + i];
    }
}

void uuid_time_v1(const struct uuid *uu, struct timeval *tv) {
    tv->tv_sec = 111111;
    tv->tv_usec = 222;
}

void uuid_time_v6(const struct uuid *uu, struct timeval *tv) {
    tv->tv_sec = 666666;
    tv->tv_usec = 666;
}

void uuid_time_v7(const struct uuid *uu, struct timeval *tv) {
    tv->tv_sec = 777777;
    tv->tv_usec = 777;
}

// Real implementation
time_t __uuid_time(const uuid_t uu, struct timeval *ret_tv) {
    struct timeval tv;
    struct uuid uuid;
    uint8_t type;

    uuid_unpack(uu, &uuid);
    type = __uuid_type(&uuid);

    switch (type) {
        case UUID_TYPE_DCE_TIME:
            uuid_time_v1(&uuid, &tv);
            break;
        case UUID_TYPE_DCE_TIME_V6:
            uuid_time_v6(&uuid, &tv);
            break;
        case UUID_TYPE_DCE_TIME_V7:
            uuid_time_v7(&uuid, &tv);
            break;
        default:
            tv.tv_sec = -1;
            tv.tv_usec = -1;
            break;
    }

    if (ret_tv)
        *ret_tv = tv;

    return tv.tv_sec;
}

int main(void) {
    uuid_t test_uuid = {
        0x12, 0x34, 0x56, 0x78,  // time_low
        0x9a, 0xbc,              // time_mid
        0x10, 0x00,              // version = 1 (UUID_TYPE_DCE_TIME)
        0xde, 0xad,              // clock seq
        0xbe, 0xef, 0xca, 0xfe, 0xba, 0xbe  // node
    };

    struct timeval tv;
    time_t t = uuid_time(test_uuid, &tv);

    printf("uuid_time result: %ld.%06ld\n", (long)t, (long)tv.tv_usec);
    ASSERT(111111, (long)t);
    ASSERT(222,  (long)tv.tv_usec);
    return 0;
}