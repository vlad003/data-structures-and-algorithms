#include <stdlib.h>
#include <stdbool.h>
#include "dlinkedlist.h"

DLINKEDLIST *dll_construct() {
    DLINKEDLIST *dll = malloc(sizeof(DLINKEDLIST));
    if (dll != NULL) {
        dll->size = 0;
        dll->begin = 0;
        dll->end = 0;
    }
    return dll;
}

RET_STATUS dll_append(DLINKEDLIST *dll, int data) {
    if (dll == NULL)
        return ST_FAIL_EMPTY;

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

RET_STATUS dll_push(DLINKEDLIST *dll, int data) {
    if (dll == NULL)
        return ST_FAIL_EMPTY;

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

RET_STATUS dll_pop(DLINKEDLIST *dll, int *ret_value) {
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

RET_STATUS dll_empty(DLINKEDLIST *dll) {
    if (dll == NULL)
        return ST_FAIL_EMPTY;
    else if (dll->size <= 0) 
        return ST_FAIL_EMPTY;
    return ST_OK;
}

RET_STATUS dll_front(DLINKEDLIST *dll, int *ret_value) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;
    *ret_value = (dll->begin)->data;
    return ST_OK;
}

RET_STATUS dll_item_at(DLINKEDLIST *dll, int index, int *ret_value) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;
    NODE *curr = dll->begin;

    for (int x = 0; x < index; ++x)
        curr = curr->next;

    *ret_value = curr->data;
    return ST_OK;
}

RET_STATUS dll_remove_at(DLINKEDLIST *dll, int index) {
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

RET_STATUS dll_range(DLINKEDLIST *dll, int begin_idx, int end_idx, DLINKEDLIST *new_list) {
    if (dll == NULL || dll->begin == NULL)
        return ST_FAIL_EMPTY;
    NODE *curr = dll->begin;

    for (int x = 0; x < begin_idx; ++x) {
        curr = curr->next;
    }

    if (!dll_empty(new_list))
        return ST_FAIL_NOT_EMPTY;

    for (int x = begin_idx; x < end_idx; ++x) {
        dll_append(new_list, curr->data);
        curr = curr->next;
    }

    return ST_OK;
}

RET_STATUS dll_insert(DLINKEDLIST *dll, int index, int item) {
    if (dll == NULL)
        return ST_FAIL_EMPTY;

    if (index >= dll->size) {
        dll_append(dll, item);
    }
    else if (index <= 0) {
        dll_push(dll, item);
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

RET_STATUS dll_destruct(DLINKEDLIST *dll) {
    if (dll == NULL)
        return ST_OK;
    
    NODE *curr = dll->begin, *new_curr;
    while (curr != NULL) {
        new_curr = curr->next;
        free(curr);
        curr = new_curr;
    }

    free(dll);
    dll = NULL;
    
    return ST_OK;
}

