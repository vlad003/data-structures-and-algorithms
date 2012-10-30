#include <stdlib.h>
#include <stdbool.h>
#include "dlinkedlist.h"

RET_STATUS append(DLINKEDLIST *dll, int data) {
    NODE *temp = malloc(sizeof(NODE));
    if (temp == NULL)
        return ST_FAIL_MALLOC;
    
    temp->data = data;
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
    return ST_OK;
}

RET_STATUS push(DLINKEDLIST *dll, int data) {
    NODE *temp = malloc(sizeof(NODE));
    if (temp == NULL)
        return ST_FAIL_MALLOC;

    temp->data = data;
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
    return ST_OK;
}

RET_STATUS pop(DLINKEDLIST *dll, int *ret_value) {
    if (dll->begin != NULL) {
        NODE *temp = dll->begin;
        dll->begin = (dll->begin)->next;
        if (dll->begin != NULL)
            (dll->begin)->prev = NULL;

        int data = temp->data;
        free(temp);

        dll->size--;

        *ret_value = data;
        return ST_OK;
    }
    return ST_FAIL_EMPTY;
}

bool empty(DLINKEDLIST *dll) {
    if (dll->size <= 0) 
        return true;
    return false;
}

RET_STATUS front(DLINKEDLIST *dll, int *ret_value) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;
    *ret_value = (dll->begin)->data;
    return ST_OK;
}

RET_STATUS item_at(DLINKEDLIST *dll, int index, int *ret_value) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;
    NODE *curr = dll->begin;

    for (int x = 0; x < index; ++x)
        curr = curr->next;

    *ret_value = curr->data;
    return ST_OK;
}

RET_STATUS remove_at(DLINKEDLIST *dll, int index) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;
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
    return ST_OK;
}

RET_STATUS range(DLINKEDLIST *dll, int begin_idx, int end_idx, DLINKEDLIST *new_list) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;
    NODE *curr = dll->begin;

    for (int x = 0; x < begin_idx; ++x) {
        curr = curr->next;
    }

    if (!empty(new_list))
        return ST_FAIL_NOT_EMPTY;

    for (int x = begin_idx; x < end_idx; ++x) {
        append(new_list, curr->data);
        curr = curr->next;
    }

    return ST_OK;
}

RET_STATUS insert(DLINKEDLIST *dll, int index, int item) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;

    if (index >= dll->size) {
        append(dll, item);
    }
    else if (index <= 0) {
        push(dll, item);
    }
    else {
        NODE *temp = malloc(sizeof(NODE));
        if (temp == NULL)
            return ST_FAIL_MALLOC;
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
    return ST_OK;

}
