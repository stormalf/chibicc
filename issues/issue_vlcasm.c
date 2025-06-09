#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define COPY16_SHIFTR(x) \
    "psrlw "x", %%xmm1\n"
#define COPY16_SHIFTL(x) \
    "psllw "x", %%xmm1\n"

#define COPY16_S(dstp, srcp, load, store, shiftstr) \
    asm volatile (                      \
        load "  0(%[src]), %%xmm1\n"    \
        shiftstr                        \
        store " %%xmm1,    0(%[dst])\n" \
        : : [dst]"r"(dstp), [src]"r"(srcp) : "memory", "xmm1")

#define COPY16(dstp, srcp, load, store) COPY16_S(dstp, srcp, load, store, "")

#define COPY64_SHIFTR(x) \
    "psrlw "x", %%xmm1\n" \
    "psrlw "x", %%xmm2\n" \
    "psrlw "x", %%xmm3\n" \
    "psrlw "x", %%xmm4\n"
#define COPY64_SHIFTL(x) \
    "psllw "x", %%xmm1\n" \
    "psllw "x", %%xmm2\n" \
    "psllw "x", %%xmm3\n" \
    "psllw "x", %%xmm4\n"

#define COPY64_S(dstp, srcp, load, store, shiftstr) \
    asm volatile (                      \
        load "  0(%[src]), %%xmm1\n"    \
        load " 16(%[src]), %%xmm2\n"    \
        load " 32(%[src]), %%xmm3\n"    \
        load " 48(%[src]), %%xmm4\n"    \
        shiftstr                        \
        store " %%xmm1,    0(%[dst])\n" \
        store " %%xmm2,   16(%[dst])\n" \
        store " %%xmm3,   32(%[dst])\n" \
        store " %%xmm4,   48(%[dst])\n" \
        : : [dst]"r"(dstp), [src]"r"(srcp) : "memory", "xmm1", "xmm2", "xmm3", "xmm4")

#define COPY64(dstp, srcp, load, store) \
    COPY64_S(dstp, srcp, load, store, "")

static void Copy2d(uint8_t *dst, size_t dst_pitch,
                   const uint8_t *src, size_t src_pitch,
                   unsigned width, unsigned height)
{
    assert(((intptr_t)src & 0x0f) == 0 && (src_pitch & 0x0f) == 0);

    for (unsigned y = 0; y < height; y++) {
        unsigned x = 0;

        bool unaligned = ((intptr_t)dst & 0x0f) != 0;
        if (!unaligned) {
            for (; x+63 < width; x += 64)
                COPY64(&dst[x], &src[x], "movdqa", "movntdq");
        } else {
            for (; x+63 < width; x += 64)
                COPY64(&dst[x], &src[x], "movdqa", "movdqu");
        }

        for (; x < width; x++)
            dst[x] = src[x];

        src += src_pitch;
        dst += dst_pitch;
    }
}


int main() {

    return 0;
}