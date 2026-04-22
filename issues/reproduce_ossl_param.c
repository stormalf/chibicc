#include <stddef.h>

typedef struct {
    const char *name;
    int type;
    const void *data;
    size_t size;
} OSSL_PARAM;

/* simulate OpenSSL macros */
#define OSSL_MAC_PARAM_DIGEST      "digest"
#define OSSL_MAC_PARAM_PROPERTIES  "props"

#define OSSL_PARAM_utf8_string(key, val, len) \
    { (key), 1, (val), (len) }

#define OSSL_PARAM_END {0, 0, 0, 0}

#ifndef kmac_new_list
static const OSSL_PARAM kmac_new_list[] = {
    OSSL_PARAM_utf8_string(OSSL_MAC_PARAM_DIGEST, NULL, 0),
    OSSL_PARAM_utf8_string(OSSL_MAC_PARAM_PROPERTIES, NULL, 0),
    OSSL_PARAM_END
};
#endif

#ifndef kmac_new_st
struct kmac_new_st {
    OSSL_PARAM *digest;
    OSSL_PARAM *propq;
};
#endif

int main(void) {
    return 0;
}
