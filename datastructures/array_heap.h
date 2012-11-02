/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE":
 * <Andrei Vacariu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include "errors.h"

enum heap_type {
    max_heap = -1,
    min_heap = 1
};

struct array_heap {
    int *heap;
    int size;
    int capacity;
    enum heap_type type;
};

typedef struct array_heap array_heap;
typedef enum heap_type heap_type;

array_heap *ahp_construct(heap_type ht);
RET_STATUS ahp_insert(array_heap *hp, int data);
RET_STATUS ahp_extract(array_heap *hp, int *ret_value);
RET_STATUS ahp_empty(array_heap *hp);
RET_STATUS ahp_destruct(array_heap *hp);
