#include <sys/sem.h>
 
 
 int
 main (void)
 {
 if (sizeof ((union semun)))
 	    return 0;
   ;
   return 0;
 }


// #include <sys/sem.h>
 
 

// //#define HAVE_UNION_SEMUN 1
// #ifndef HAVE_UNION_SEMUN
// union semun {
// 	int val;
// 	struct semid_ds *buf;
// 	unsigned short int *array;
// 	struct seminfo *__buf;
// };
// #endif

// static int remove_id(int type, int iskey, int id)
// {
//         int ret;
// 	char *errmsg;
// 	/* needed to delete semaphores */
// 	union semun arg;
//     arg.val = 0;
//     return 0;
// }

// int main() {
    
//     return 0;
// }