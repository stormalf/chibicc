#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main() {
    union semun sem_union;
    if (sizeof(sem_union) > 0)
        return 0;
    return 1;
}
