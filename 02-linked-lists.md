# Linked Lists

A linked list is a sequence of elements which allows insertion and deletion of
elements, and so can grow and shrink. Each element in the list is called a
_node_ and it holds a pointer to one or both of its neighbours. In the former
case, it is called a _singly-linked list_ and in the latter, a _doubly-linked
list_.

This document will describe a singly-linked list.

## Implementation and usage

Since a linked list is a collection of nodes, we need to define what a node
looks like, and what data it contains. A node can be defined using a `struct`
such as the following (assuming the data we wish to store is an `int`).

```c
struct node {
    int data;
    struct node *next;
};
```

For convenience, we will also define a struct to hold our initial node, and
some other details about the list.

```c
struct list {
    int size;
    struct node *begin;
};
```

Now that we have our structs, we'll want to create a new empty list. We'll need
to allocate the memory for it, and then initialize its values.

```c
struct list *L = malloc(sizeof(struct list));
L->size = 0;
L->begin = NULL;
```

### Appending elements

To append an element to a linked list, we need to create a allocate memory for
a new node, store our data within it, and then get the last element of our list
to point to it.

```c
struct node *x = malloc(sizeof(struct node));
x->data = 5;    // this is where we store our integer in the node
x->next = NULL; // the last element of the list doesn't have anything after it

// if the list is empty, we put the node at the beginning
if (L->begin == NULL) {
    L->begin = x;
    L->size++;
} else {
    // find the last node
    struct node *last = L->begin;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = x;
    L->size++;
}
```

Note that while keeping track of the size of the list isn't necessary for
making the list work, it's more efficient than having to traverse the entire
list every time you need to check the length.

### Prepending elements

To prepend an element, one simply needs to change which node the list struct
considers the beginning.

```c
struct node *x = malloc(sizeof(struct node));
x->data = 5;
x->next = L->begin;
L->begin = x;
L->size++;
```

### Inserting elements

Suppose you have a node `x` with its `data` attribute set, and you want to
insert it in position 6. Assuming the list has more than 6 elements, this is
what you need to do:

```c
struct node *prev = L->begin;  // this is going to be the node in position 5

for (int i = 0; i < 5; i++) {
    prev = prev->next;
}

x->next = prev->next;
prev->next = x;
L->size++;
```

Note that we have 5 in the `for` loop and not 6. It is 1 less than the position
we're inserting at since we want the previous node.

For a simple example, look at the case where the list has 5 elements, and we
want to insert at position 2. In this case, we need `prev` to point to the
second node in the list (at index 1).

    The list:
    0 -> 1 -> 2 -> 3 -> 4 -> NULL;

    After setting the initial value of `prev`:
    0 -> 1 -> 2 -> 3 -> 4 -> NULL;
    ^

    After 1 iteration:
    0 -> 1 -> 2 -> 3 -> 4 -> NULL;
         ^

We get that one iteration using `for (int i = 0; i < 1; i++) { }`.

### Deleting elements

To delete an element, we follow a similar procedure to insertion. We first find
the previous element, and then modify the pointers.

Suppose we want to remove the node at position 6.

```c
struct node *prev = L->begin;  // this is going to be the node in position 5

for (int i = 0; i < 5; i++) {
    prev = prev->next;
}

struct node *to_delete = prev->next;
prev->next = to_delete->next;
free(to_delete);
L->size--;
```

## Efficiency

Appending to a list is O(n) since you have to traverse the list to do it. This
can be improved to O(1) by keeping track of the end node in the `list` struct.

Prepending to a list is O(1) since you only have to switch two pointers.

Insertion and deletion is O(n) since you have to traverse the list to the
necessary position. Switching the pointers is O(1).
