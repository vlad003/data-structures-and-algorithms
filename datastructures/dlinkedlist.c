#include <stdlib.h>
#include <stdbool.h>
#include "dlinkedlist.h"

void append(DLINKEDLIST *dll, int item) {
    NODE *temp = malloc(sizeof(NODE));
    
    temp->data = item;
    temp->prev = dll->end;
    temp->next = NULL;

    if (dll->begin != NULL) {
        (dll->end)->next = temp;
    }

    else if (dll->begin == NULL) {
        dll->begin = temp;
        temp->prev = NULL;
    }

    dll->end = temp;

    dll->size++;
}

void push(DLINKEDLIST *dll, int item) {
    NODE *temp = malloc(sizeof(NODE));

    temp->data = item;
    temp->next = dll->begin;
    temp->prev = NULL;

    if (dll->begin != NULL) {
        (dll->begin)->prev = temp;
    }
    else if (dll->begin == NULL) {
        dll->end = temp;
    }

    dll->begin = temp;

    dll->size++;
}

int pop(DLINKEDLIST *dll) {
    if (dll->begin != NULL) {
        NODE *temp = dll->begin;
        dll->begin = (dll->begin)->next;
        if (dll->begin != NULL)
            (dll->begin)->prev = NULL;

        int data = temp->data;
        free(temp);

        dll->size--;

        return data;
    }
}

bool empty(DLINKEDLIST *dll) {
    if (dll->size <= 0) 
        return true;
    return false;
}

int front(DLINKEDLIST *dll) {
    return (dll->begin)->data;
}

int item_at(DLINKEDLIST *dll, int index) {
    NODE *curr = dll->begin;

    for (int x = 0; x < index; ++x)
        curr = curr->next;

    return curr->data;
}

void remove_at(DLINKEDLIST *dll, int index) {
    NODE *curr = dll->begin;  

    for (int x = 0; x < index; ++x) {
        curr = curr->next;
    }

    if (curr->prev != NULL)
        (curr->prev)->next = curr->next;
    else if (curr->prev == NULL)
        dll->begin = curr->next;

    if (curr->next != NULL)
        (curr->next)->prev = curr->prev;
    else if (curr->next == NULL)
        dll->end = curr->prev;

    free(curr);

    dll->size--;
}

DLINKEDLIST* range(DLINKEDLIST *dll, int begin_idx, int end_idx) {
    NODE *curr = dll->begin;

    for (int x = 0; x < begin_idx; ++x) {
        curr = curr->next;
    }

    DLINKEDLIST *dll_range = malloc(sizeof(DLINKEDLIST));
    dll_range->begin = NULL;
    dll_range->end = NULL;
    dll_range->size = 0;

    for (int x = begin_idx; x < end_idx; ++x) {
        append(dll_range, curr->data);
        curr = curr->next;
    }

    return dll_range;
}

void insert(DLINKEDLIST *dll, int index, int item) {
    if (index >= dll->size) {
        append(dll, item);
    }
    else if (index <= 0) {
        push(dll, item);
    }
    else {
        NODE *temp = malloc(sizeof(NODE));
        temp->data = item;

        NODE *curr = dll->begin;

        for (int x = 0; x < index; ++x) {
            curr = curr->next;
        }

        temp->next = curr;
        temp->prev = curr->prev;
        (curr->prev)->next = temp;
        curr->prev = temp;

        dll->size++;
    }

}
