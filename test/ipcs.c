#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <sys/msg.h>
#include <stddef.h>

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
    printf("msgmax offset = %zu\n", offsetof(struct msginfo, msgmax));
    printf("msgmnb offset = %zu\n", offsetof(struct msginfo, msgmnb));
    printf("msgtql offset = %zu\n", offsetof(struct msginfo, msgtql));
    #ifdef MSG_INFO
        printf("MSG_INFO defined as %d\n", MSG_INFO);
    #else
        printf("MSG_INFO not defined\n");
    #endif
    return 0;
}
