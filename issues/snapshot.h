#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
// snapshot.h
typedef unsigned int TransactionId;
typedef unsigned int CommandId;
typedef unsigned int uint32;
typedef int int32;
typedef long long uint64;
typedef struct pairingheap_node { void *dummy; } pairingheap_node;
typedef struct GlobalVisState { int dummy; } GlobalVisState;
typedef long TimestampTz;
typedef long long XLogRecPtr;

typedef enum SnapshotType
{
	SNAPSHOT_MVCC,
	SNAPSHOT_SELF,
	SNAPSHOT_ANY
} SnapshotType;

typedef struct SnapshotData
{
	SnapshotType snapshot_type;
	TransactionId xmin;
	TransactionId xmax;
	TransactionId *xip;
	uint32 xcnt;
	TransactionId *subxip;
	int32 subxcnt;
	bool suboverflowed;
	bool takenDuringRecovery;
	bool copied;
	CommandId curcid;
	uint32 speculativeToken;
	struct GlobalVisState *vistest;
	uint32 active_count;
	uint32 regd_count;
	pairingheap_node ph_node;
	TimestampTz whenTaken;
	XLogRecPtr lsn;
	uint64 snapXactCompletionCount;
} SnapshotData;
