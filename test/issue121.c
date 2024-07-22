
//#include <libavutil/common.h>
#include <assert.h>
#include <stddef.h>
#include <stdatomic.h>
#include <stdalign.h>
#include <stdio.h> 


struct big_align_struct {
    long long ll;
    double d;
};


// test
typedef struct PodTag
{
   int i;
   double d;
   char c;
} PodType;
 
struct vcddev_s
{
    char *psz_dev; /* vcd device name */

    /* Section used in vcd image mode */
    int i_vcdimage_handle;
};

typedef struct vcddev_s vcddev_t;

struct vlc_suuint { union { unsigned int value; }; };

typedef struct
{
    vcddev_t *vcddev;  /* vcd device descriptor */
    unsigned start;    /**< Track first sector */
    unsigned length;   /**< Track total sectors */
    unsigned position; /**< Current offset within track sectors */
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
    alignof(struct big_align_struct),
    alignof(void *),
    alignof(max_align_t),
};

static_assert(sizeof(atomic_uint) <= sizeof(struct vlc_suuint),
              "Size mismatch");


int main(void)
{

    printf("%llu\n", offsetof(PodType, c));
    static_assert(alignof(atomic_uint) <= alignof(struct vlc_suuint),
                "Alignment mismatch");

    printf("%llu\n", alignof(atomic_uint));
    printf("%llu\n", alignof(struct vlc_suuint));
    return 0;
}