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

void append(DLINKEDLIST *dll, int data); // same as enqueue
int pop(DLINKEDLIST *dll); // same as dequeue
bool empty(DLINKEDLIST *dll);
int item_at(DLINKEDLIST *dll, int index);
int front(DLINKEDLIST *dll);
void push(DLINKEDLIST *dll, int item); // adds to the front
void remove_at(DLINKEDLIST *dll, int index);
// begin_idx is included, end_idx is not
DLINKEDLIST* range(DLINKEDLIST *dll, int begin_idx, int end_idx);
// if index is <=0, it pushes. index >= dll->size appends;
void insert(DLINKEDLIST *dll, int index, int item);
