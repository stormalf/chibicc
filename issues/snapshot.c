#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int SnapshotType;
typedef unsigned int TransactionId;
typedef unsigned int CommandId;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned long long uint64;
typedef long long TimestampTz;
typedef unsigned long long XLogRecPtr;

typedef struct pairingheap_node {
  // dummy placeholder for this example
  void *dummy;
} pairingheap_node;

typedef struct SnapshotData {
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
    void *vistest;

    uint32 active_count;
    uint32 regd_count;
    pairingheap_node ph_node;

    TimestampTz whenTaken;
    XLogRecPtr lsn;

    uint64 snapXactCompletionCount;
} SnapshotData;

typedef SnapshotData* Snapshot;

// Function to copy a Snapshot and mark copied=1
Snapshot CopySnapshot(Snapshot snapshot) {
    if (!snapshot) return NULL;

    Snapshot copy = malloc(sizeof(SnapshotData));
    if (!copy) {
        perror("malloc");
        exit(1);
    }

    memcpy(copy, snapshot, sizeof(SnapshotData));
    copy->copied = true;  // Mark the copy as copied
    return copy;
}

Snapshot RegisterSnapshot(Snapshot snapshot) {
    if (!snapshot) return NULL;

    // If already copied, reuse snapshot; else copy it.
    Snapshot snap = snapshot->copied ? snapshot : CopySnapshot(snapshot);
    printf("RegisterSnapshot snapshot=%p copied=%d\n", snapshot, snapshot->copied);
    printf("RegisterSnapshot copy->copied=%d\n", snap->copied);

    // Simulate refcounting
    snap->regd_count++;
    printf("RegisterSnapshot snap->regd_count=%u\n", snap->regd_count);

    return snap;
}

int main(void) {
    Snapshot original = malloc(sizeof(SnapshotData));
    if (!original) {
        perror("malloc");
        return 1;
    }
    memset(original, 0, sizeof(SnapshotData));
    original->copied = false;
    original->regd_count = 0;

    // Call RegisterSnapshot multiple times
    for (int i = 0; i < 3; i++) {
        Snapshot snap = RegisterSnapshot(original);
        // free the copied snapshot only if it's a new copy
        if (snap != original) {
            free(snap);
        }
    }

    free(original);
    return 0;
}
