#include <stdio.h>
#include <assert.h>


static int common_local;



#define BLCKSZ 512
#define SizeOfPageHeaderData 128
typedef struct PageHeaderData {
    int pd_special;
} PageHeaderData;

typedef struct PageData {
    int pd_special;
} PageData;

static inline void
PageValidateSpecialPointer(const PageData *page)
{
	assert(page);
	assert(((const PageHeaderData *) page)->pd_special <= BLCKSZ);
	assert(((const PageHeaderData *) page)->pd_special >= SizeOfPageHeaderData);
}



int main() {
    printf("Ok\n");
    return 0;
}