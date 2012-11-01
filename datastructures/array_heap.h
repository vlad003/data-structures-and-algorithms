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

array_heap *ahp_create(heap_type ht);
RET_STATUS ahp_insert(array_heap *hp, int data);
RET_STATUS ahp_extract(array_heap *hp, int *ret_value);
RET_STATUS ahp_empty(array_heap *hp);
RET_STATUS ahp_clear(array_heap *hp);
