#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

// Mimic PostgreSQL types
typedef unsigned int Oid;
typedef int16_t int16;
typedef int32_t int32;
typedef char bool;

#define NAMEDATALEN 64

typedef struct nameData {
    char data[NAMEDATALEN];
} NameData;

// Mimic FormData_pg_attribute
typedef struct FormData_pg_attribute {
    Oid attrelid;
    NameData attname;
    Oid atttypid;
    int16 attlen;
    int16 attnum;
    int32 atttypmod;
    int16 attndims;
    bool attbyval;
    char attalign;
    char attstorage;
    char attcompression;
    bool attnotnull;
    bool atthasdef;
    bool atthasmissing;
    char attidentity;
    char attgenerated;
    bool attisdropped;
    bool attislocal;
    int16 attinhcount;
    Oid attcollation;
} FormData_pg_attribute;

int main(void) {
    printf("sizeof(FormData_pg_attribute) = %zu\n", sizeof(FormData_pg_attribute));
    printf("sizeof(NameData) = %zu\n", sizeof(NameData));
    printf("offsetof attrelid = %zu\n", offsetof(FormData_pg_attribute, attrelid));
    printf("offsetof attname = %zu\n", offsetof(FormData_pg_attribute, attname));
    printf("offsetof atttypid = %zu\n", offsetof(FormData_pg_attribute, atttypid));
    printf("offsetof attlen = %zu\n", offsetof(FormData_pg_attribute, attlen));
    printf("offsetof attnum = %zu\n", offsetof(FormData_pg_attribute, attnum));
    printf("offsetof atttypmod = %zu\n", offsetof(FormData_pg_attribute, atttypmod));
    printf("offsetof attndims = %zu\n", offsetof(FormData_pg_attribute, attndims));
    printf("offsetof attbyval = %zu\n", offsetof(FormData_pg_attribute, attbyval));
    printf("offsetof attalign = %zu\n", offsetof(FormData_pg_attribute, attalign));
    printf("offsetof attstorage = %zu\n", offsetof(FormData_pg_attribute, attstorage));
    printf("offsetof attcompression = %zu\n", offsetof(FormData_pg_attribute, attcompression));
    printf("offsetof attnotnull = %zu\n", offsetof(FormData_pg_attribute, attnotnull));
    printf("offsetof atthasdef = %zu\n", offsetof(FormData_pg_attribute, atthasdef));
    printf("offsetof atthasmissing = %zu\n", offsetof(FormData_pg_attribute, atthasmissing));
    printf("offsetof attidentity = %zu\n", offsetof(FormData_pg_attribute, attidentity));
    printf("offsetof attgenerated = %zu\n", offsetof(FormData_pg_attribute, attgenerated));
    printf("offsetof attisdropped = %zu\n", offsetof(FormData_pg_attribute, attisdropped));
    printf("offsetof attislocal = %zu\n", offsetof(FormData_pg_attribute, attislocal));
    printf("offsetof attinhcount = %zu\n", offsetof(FormData_pg_attribute, attinhcount));
    printf("offsetof attcollation = %zu\n", offsetof(FormData_pg_attribute, attcollation));
    return 0;
}
