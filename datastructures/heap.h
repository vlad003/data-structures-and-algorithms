#include "errors.h"

enum { max_heap, min_heap } heap_type;

struct bt_node {
    int data;
    struct node *parent, *left, *right;
};

struct heap {
    int size;
    heap_type type;
    struct node *root;
    struct node *extremity; // represents either the smallest or largest node
};

typedef struct bt_node BT_NODE;
typedef struct heap HEAP;

RET_STATUS hp_insert(HEAP *hp, int data);
//RET_STAUS hp_extract(HEAP *hp, int *ret_value);
RET_STATUS hp_empty(HEAP *hp);
