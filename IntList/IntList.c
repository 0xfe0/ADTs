#include "IntList.h"

IntList IntList_Create()
{
    return NULL;
}

void
IntList_Cons(IntList *listRef, IntListItem value)
{
    IntList new = malloc(sizeof(struct IntListObj));
    new->item = value;
    new->next = *listRef;
    *listRef = new;
}

IntListItem IntList_DelHead(IntList *listRef)
{
    IntList new;
    IntListItem value;

    new = *listRef;
    *listRef = Tail(new); value = Head(new);
    free(new);
    return value;
}

_Bool Int_Read(FILE *file, int *valueRef)
{
    return fscanf(file, "%d", valueRef) == 1;
}

IntList IntList_Read(FILE *fin)
{
    IntListItem     value;
    IntList         result;

    result = IntList_Create();
    while(Int_Read(fin, &value))
        IntList_Cons(&result, value);
    
    IntList_Reverse(&result);

    return result;
}

void IntList_Reverse(IntList *listRef)
{
    IntList     p;
    IntList     rev;
    IntList     q;

    p = *listRef;
    rev = NULL;
    while(p != NULL) {
        q = p;
        p = p->next;
        q->next = rev;
        rev = q;
    }

    *listRef = rev;
}

void
IntList_Traverse(IntList list, Generic handle, ItemInspector func)
{
    IntList p;
    for(p = list; !IsEmpty(p); p = Tail(p)) {
        func(handle, Head(p));
    }
}

void IntWrite(Generic handle, int value)
{
    fprintf((FILE *) handle, " %d", value);
}

void IntList_Write(IntList list, FILE *fout)
{
    IntList_Traverse(list , (Generic) fout, IntWrite);
    fprintf(fout, "\n");
}

IntList IntList_Builder(Generic handle, ItemGenerator getItem)
{
    IntList result;
    IntList *lp;

    IntList q;
    IntListItem     value;

    lp = &result;

    while(getItem(handle, &value)) {
        q = malloc(sizeof(IntListItem));
        q->item = value;
        *lp = q;
        lp = &q->next;
    }

    *lp = NULL;
    return result;
}
