#include <sys/ipc.h>
#include <sys/sem.h>

#include <sys/msg.h>
#include "test.h"

int main() {
    int id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (id < 0) {
        perror("semget failed");
        return 1;
    }

    struct semid_ds buf;
    int ret = semctl(id, 0, IPC_STAT, &buf);
    if (ret < 0) {
        perror("semctl IPC_STAT failed");
    } else {
        printf("semctl IPC_STAT succeeded\n");
    }

    semctl(id, 0, IPC_RMID);
    printf("sizeof(msginfo) = %zu\n", sizeof(struct msginfo));
    ASSERT(32, sizeof(struct msginfo));
    printf("msgmax offset = %zu\n", offsetof(struct msginfo, msgmax));
    ASSERT(8, offsetof(struct msginfo, msgmax) );
    printf("msgmnb offset = %zu\n", offsetof(struct msginfo, msgmnb));
    ASSERT(12, offsetof(struct msginfo, msgmnb));
    printf("msgtql offset = %zu\n", offsetof(struct msginfo, msgtql));
    ASSERT(24, offsetof(struct msginfo, msgtql));
    return 0;
}
