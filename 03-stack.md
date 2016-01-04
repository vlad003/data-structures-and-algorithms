# Stack

A stack is a sequence of elements which allow you to add things to one end, and
you can only remove things one at a time from the same end. Think of a stack of
plates; you put a plate on top of the stack, and if you want to remove a plate,
you take it off the top of the stack.

## Implementation and usage

There are two simple ways of implementing a stack: a standard array, or a
linked list. We'll implement an array-based stack here and only mention the
equivalent if you're using a linked-list.

As expected, using an array will limit the maximum size of the stack, so for
this example, let's say we want a stack that will only ever have at most 10
items. Since we're using an array, we won't know how many elements we have in
our stack unless we keep track of it ourselves.

```c
struct stack {
    int elements[10];
    int size;
}

struct stack *S = malloc(sizeof(struct stack));
S->size = 0;
```

There are two main operations we can perform on a stack: *push* and *pop*.
Pushing is adding an element to the top of the stack, and popping is removing
the element off the top of the stack.

```c
int push(struct stack *S, int elem)
{
    if (S->size == 10)
        return -1;

    S->elements[S->size + 1] = elem;
    S->size++;

    return 0;
}

int pop(struct stack *S)
{
    return S->elements[S->size--];
}
```

If you were implementing a stack using a linked list, your `push` operation
would be identical to the `prepend` operation mentioned in the linked-list
article, and the `pop` operation would simply be accessing the first element of
the list and then removing it.

The reason for using the front of a linked list rather than the end is simply
efficiency.

## Efficiency

Since operations on stacks (whether using linked-lists or arrays) is simply
accessing a known place in memory and adjusting a counter, all operations on
stacks are O(1).
