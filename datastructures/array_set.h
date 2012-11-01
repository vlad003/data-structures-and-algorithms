#include "errors.h"

struct set {
    int size;
    int capacity;
    int *set;
};

typedef struct set set;

set *set_construct();
set *set_construct_from(int *data_array);
RET_STATUS set_add(set *st, int data);
RET_STATUS set_remove(set *st, int data);
RET_STATUS set_union(set *s, set *t, set *destination);
RET_STATUS set_intersection(set *s, set *t, set *destination);
RET_STATUS set_difference(set *s, set *t, set *destination);
RET_STATUS set_subset(set *s, set *t);

RET_STATUS set_contains(set *s, int data);
RET_STATUS set_empty(set *s);

