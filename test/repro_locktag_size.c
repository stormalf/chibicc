#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint8_t uint8;

typedef enum LockTagType
{
	LOCKTAG_RELATION,
	LOCKTAG_RELATION_EXTEND,
	LOCKTAG_DATABASE_FROZEN_IDS,
	LOCKTAG_PAGE,
	LOCKTAG_TUPLE,
	LOCKTAG_TRANSACTION,
	LOCKTAG_VIRTUALTRANSACTION,
	LOCKTAG_SPECULATIVE_TOKEN,
	LOCKTAG_OBJECT,
	LOCKTAG_USERLOCK,
	LOCKTAG_ADVISORY,
	LOCKTAG_APPLY_TRANSACTION
} LockTagType;

typedef struct LOCKTAG
{
	uint32		locktag_field1; /* a 32-bit ID field */
	uint32		locktag_field2; /* a 32-bit ID field */
	uint32		locktag_field3; /* a 32-bit ID field */
	uint16		locktag_field4; /* a 16-bit ID field */
	uint8		locktag_type;	/* see enum LockTagType */
	uint8		locktag_lockmethodid;	/* lockmethod indicator */
} LOCKTAG;

typedef int LOCKMODE;

typedef struct LOCALLOCKTAG
{
	LOCKTAG		lock;			/* identifies the lockable object */
	LOCKMODE	mode;			/* lock mode for this table entry */
} LOCALLOCKTAG;

struct T {
    char a;
    long b;
    char c;
};


struct Big {
    char buf[128];
    long x;
    int y;
};


int main() {
    printf("LOCKTAG:\n");
    printf("  size: %zu\n", sizeof(LOCKTAG));
    printf("  field1 offset: %zu\n", offsetof(LOCKTAG, locktag_field1));
    printf("  field2 offset: %zu\n", offsetof(LOCKTAG, locktag_field2));
    printf("  field3 offset: %zu\n", offsetof(LOCKTAG, locktag_field3));
    printf("  field4 offset: %zu\n", offsetof(LOCKTAG, locktag_field4));
    printf("  type offset: %zu\n", offsetof(LOCKTAG, locktag_type));
    printf("  methodid offset: %zu\n", offsetof(LOCKTAG, locktag_lockmethodid));

    printf("LOCALLOCKTAG:\n");
    printf("  size: %zu\n", sizeof(LOCALLOCKTAG));
    printf("  lock offset: %zu\n", offsetof(LOCALLOCKTAG, lock));
    printf("  mode offset: %zu\n", offsetof(LOCALLOCKTAG, mode));

    char buf[64];
    size_t n = 64;

    memset(buf, 0x11, n);

    for (int i = 0; i < 64; i++)
        assert((unsigned char)buf[i] == 0x11);

    puts("OK");
    memset(buf, 0, sizeof(buf));

    memcpy(buf + 4, "abcd", 4);

    assert(buf[4] == 'a');
    assert(buf[7] == 'd');

    puts("OK");
        struct T x;
    memset(&x, 0xAB, sizeof(x));

    struct T y = x;

    unsigned char *p = (unsigned char *)&y;

    for (size_t i = 0; i < sizeof(y); i++)
        assert(p[i] == 0xAB);

    puts("OK");

    struct Big a;
    struct Big b;

    memset(&a, 0xCD, sizeof(a));
    memcpy(&b, &a, sizeof(a));

    unsigned char *p2 = (unsigned char *)&b;
    for (size_t i = 0; i < sizeof(b); i++)
        assert(p2[i] == 0xCD);

    puts("OK");    

    return 0;
}
