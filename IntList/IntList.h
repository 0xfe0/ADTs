//the IntList ADT Specification

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int IntListItem;
typedef struct IntListObj* IntList;
typedef void* Generic;

typedef void (*ItemInspector) (Generic handle, IntListItem value);
typedef bool (*ItemGenerator) (Generic handle, IntListItem *valueRef);

typedef struct IntListObj{
    IntList     next;
    IntListItem item;
} IntListObj;


IntList IntList_Create();
void IntList_Cons(IntList *listRef, IntListItem value);
IntListItem IntList_DelHead(IntList *listRef);
void IntList_Reverse(IntList *listRef);
void IntList_Traverse(IntList list, Generic handle, ItemInspector func);
IntList IntList_Read(FILE *fin);
void IntList_Write(IntList list, FILE *fout);
IntList IntList_Build(Generic handle, ItemGenerator func);

#define IsEmpty(list)       ((list) == NULL)
#define NonEmpty(list)      ((list) != NULL)

#define Head(list)          (NonEmpty(list), (list)->item)
#define Tail(list)          (NonEmpty(list), (list)->next)
