#include "errors.h"

enum heap_type { max_heap, min_heap };

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

RET_STATUS hp_insert(HEAP *hp, int data);
//RET_STAUS hp_extract(HEAP *hp, int *ret_value);
RET_STATUS hp_empty(HEAP *hp);
