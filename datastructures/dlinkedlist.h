/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE":
 * <Andrei Vacariu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

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

DLINKEDLIST *dll_construct();
RET_STATUS dll_append(DLINKEDLIST *dll, int data); // same as enqueue
RET_STATUS dll_push(DLINKEDLIST *dll, int data); // adds to the front
RET_STATUS dll_pop(DLINKEDLIST *dll, int *ret_value); // same as dequeue
RET_STATUS dll_empty(DLINKEDLIST *dll);
RET_STATUS dll_item_at(DLINKEDLIST *dll, int index, int *ret_value);
RET_STATUS dll_front(DLINKEDLIST *dll, int *ret_value);
RET_STATUS dll_remove_at(DLINKEDLIST *dll, int index);
// begin_idx is included, end_idx is not
RET_STATUS dll_range(DLINKEDLIST *dll, int begin_idx, int end_idx, DLINKEDLIST *new_list);
// if index is <=0, it pushes. index >= dll->size appends;
RET_STATUS dll_insert(DLINKEDLIST *dll, int index, int item);
RET_STATUS dll_destruct(DLINKEDLIST *dll);
