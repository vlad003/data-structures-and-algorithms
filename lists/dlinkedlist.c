#include <stdlib.h>
#include <stdio.h>
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
    

    


