#include <assert.h>
#include <stddef.h>
#include <stdatomic.h>
#include <stdalign.h>
#include <stdio.h>
#include <stdint.h>

// Define struct big_align_struct to avoid the error
typedef struct {
    char a;
    double b;
} big_align_struct;


// Define vlc_suuint structure
typedef struct {
    uint64_t value;
} vlc_suuint;

 
struct vcddev_s
{
    char *psz_dev; /* vcd device name */

    /* Section used in vcd image mode */
    int i_vcdimage_handle;
};

typedef struct vcddev_s vcddev_t;

// Define other types
typedef struct PodTag {
    int i;
    double d;
    char c;
} PodType;

typedef struct {
    vcddev_t *vcddev;
    unsigned start;
    unsigned length;
    unsigned position;
} demux_sys_t;

static_assert(offsetof(demux_sys_t, vcddev) == 0, "Invalid cast");

static const size_t alignv[] = {
    alignof(char),
    alignof(short),
    alignof(int),
    alignof(long),
    alignof(long long),
    alignof(float),
    alignof(double),
    alignof(big_align_struct),
    alignof(void *),
    alignof(max_align_t),
    alignof(vlc_suuint), // Added alignment check for vlc_suuint
};

static_assert(sizeof(atomic_uint) <= sizeof(vlc_suuint),
              "Size mismatch");

static_assert(alignof(atomic_uint) <= alignof(vlc_suuint),
              "Alignment mismatch");

int main(void) {
    printf("%llu\n", offsetof(PodType, c));
    printf("%llu\n", alignof(atomic_uint));
    printf("%llu\n", alignof(vlc_suuint));
    return 0;
}
