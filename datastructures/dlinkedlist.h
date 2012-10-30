#include "errors.h"

struct node {
    int data;
    struct node *next, *prev;
};

struct dlinkedlist {
    int size;
    struct node *begin, *end;
};

typedef struct node NODE;
typedef struct dlinkedlist DLINKEDLIST;

RET_STATUS append(DLINKEDLIST *dll, int data); // same as enqueue
RET_STATUS push(DLINKEDLIST *dll, int data); // adds to the front
RET_STATUS pop(DLINKEDLIST *dll, int *ret_value); // same as dequeue
bool empty(DLINKEDLIST *dll);
RET_STATUS item_at(DLINKEDLIST *dll, int index, int *ret_value);
RET_STATUS front(DLINKEDLIST *dll, int *ret_value);
RET_STATUS remove_at(DLINKEDLIST *dll, int index);
// begin_idx is included, end_idx is not
RET_STATUS range(DLINKEDLIST *dll, int begin_idx, int end_idx, DLINKEDLIST *new_list);
// if index is <=0, it pushes. index >= dll->size appends;
RET_STATUS insert(DLINKEDLIST *dll, int index, int item);
