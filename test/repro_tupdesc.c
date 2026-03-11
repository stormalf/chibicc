#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint32_t Oid;
typedef int32_t int32;
typedef int16_t int16;
typedef uint8_t uint8;

typedef struct CompactAttribute
{
	int32		attcacheoff;
	int16		attlen;
	bool		attbyval;
	bool		attispackable;
	bool		atthasmissing;
	bool		attisdropped;
	bool		attgenerated;
	char		attnullability;
	uint8		attalignby;
} CompactAttribute;

typedef char NameData[64];

typedef struct FormData_pg_attribute
{
	Oid			attrelid;
	NameData	attname;
	Oid			atttypid;
	int16		attlen;
	int16		attnum;
	int32		atttypmod;
	int16		attndims;
	bool		attbyval;
	char		attalign;
	char		attstorage;
	char		attcompression;
	bool		attnotnull;
	bool		atthasdef;
	bool		atthasmissing;
	char		attidentity;
	char		attgenerated;
	bool		attisdropped;
	bool		attislocal;
	int16		attinhcount;
	Oid			attcollation;
} FormData_pg_attribute;

typedef struct TupleDescData
{
	int			natts;
	Oid			tdtypeid;
	int32		tdtypmod;
	int			tdrefcount;
	void        *constr;
	CompactAttribute compact_attrs[];
} TupleDescData;

int main() {
    printf("sizeof(CompactAttribute) = %zu\n", sizeof(CompactAttribute));
    printf("alignof(CompactAttribute) = %zu\n", __alignof__(CompactAttribute));
    
    printf("sizeof(FormData_pg_attribute) = %zu\n", sizeof(FormData_pg_attribute));
    printf("alignof(FormData_pg_attribute) = %zu\n", __alignof__(FormData_pg_attribute));

    printf("offsetof(TupleDescData, compact_attrs) = %zu\n", offsetof(TupleDescData, compact_attrs));
    
    printf("offsetof(FormData_pg_attribute, atttypid) = %zu\n", offsetof(FormData_pg_attribute, atttypid));
    printf("offsetof(FormData_pg_attribute, attcollation) = %zu\n", offsetof(FormData_pg_attribute, attcollation));

    return 0;
}
