#include "errors.h"

enum heap_type {
    max_heap = -1,
    min_heap = 1
};


struct bt_node {
    int data;
    struct bt_node *parent, *left, *right;
};

struct heap {
    int size;
    enum heap_type type;
    struct bt_node *root;
    struct bt_node *extremity; // represents either the smallest or largest node
};

typedef struct bt_node BT_NODE;
typedef struct heap HEAP;

HEAP *hp_create(heap_type ht);
RET_STATUS hp_insert(HEAP *hp, int data);
RET_STATUS hp_extract(HEAP *hp, int *ret_value);
RET_STATUS hp_empty(HEAP *hp);
RET_STATUS hp_clear(HEAP *hp);
