
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

int main() {

    return 0;
}