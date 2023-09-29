#include "vlc_common.h"

/** Player capability: can seek */
#define VLC_PLAYER_CAP_SEEK (1<<0)

VLC_API int
vlc_player_GetCapabilities(char *player);

/**
 * Helper to get the seek capability
 */
static inline bool
vlc_player_CanSeek(char *player)
{
    return vlc_player_GetCapabilities(player) & VLC_PLAYER_CAP_SEEK;
}

#ifndef __cplusplus
#define vlc_hash_FinishHex(ctx, output)                             \
    do {                                                            \
        char out_tmp[_Generic((ctx),                                \
            vlc_hash_md5_t *: VLC_HASH_MD5_DIGEST_SIZE)];           \
        _Generic((ctx),                                             \
            vlc_hash_md5_t *: vlc_hash_md5_Finish)                  \
        (ctx, out_tmp, sizeof(out_tmp));                            \
        vlc_hex_encode_binary(out_tmp, sizeof(out_tmp), output);    \
    } while (0)
#endif
VLC_API void vlc_hash_md5_Finish(vlc_hash_md5_t *ctx, void *output, size_t size);

int main() {
vlc_hash_md5_t md5; 
    return 0;
}