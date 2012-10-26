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
// range(DLINKEDLIST *dll, int begin_idx, int end_idx);