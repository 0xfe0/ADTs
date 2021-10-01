#include "IntList.h"

struct stats {
    size_t tally;
    long sum;
};

void tally_up(Generic handle, IntListItem value)
{
    struct stats        *sp = handle;
    sp->tally++;
    sp->sum += value;
}

void print(Generic meanRef, IntListItem value)
{
    if(value > *((float *)meanRef)) {
        printf("%d\n");
    }
}

int main()
{
    IntList         list;
    struct stats    stats;
    float           mean;

    list = IntList_Read(stdin);
    stats.tally = 0; stats.sum = 0;
    IntList_Traverse(list, (Generic) &stats, tally_up);
    if(stats.tally > 0) {
        mean = 0;
        puts("This is output print:");
        IntList_Traverse(list, (Generic) &mean, print);
    }

    return 0;
}
