/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE":
 * <Andrei Vacariu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

#include <stdlib.h>
#include "array_heap.h"

void swap(int *x, int *y) {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

array_heap *ahp_construct(heap_type ht) {
    array_heap *hp = malloc(sizeof(array_heap));
    if (hp != NULL) {
        hp->heap = malloc(sizeof(int) * 16);
        hp->capacity = 16;
        hp->size = 0;
        hp->type = ht;
    }

    return hp;
}

RET_STATUS ahp_insert(array_heap *hp, int data) {
    if (hp == NULL)
        return ST_FAIL_EMPTY;

    if (hp->size == hp->capacity) {
        // array is filled, we need to enlarge it
        int *new = realloc(hp->heap, sizeof(int) * hp->capacity * 2);
        if (new == NULL)
            return ST_FAIL_MALLOC;
        hp->capacity *= 2;
        hp->heap = new;
    }

    hp->heap[hp->size] = data;

    // trickle up
    int current = hp->size;
    int parent = (current - 1) / 2;

    while (hp->type * hp->heap[current] < hp->type * hp->heap[parent]) {
        swap(&(hp->heap[current]), &(hp->heap[parent]));
        current = parent;
        parent = (current - 1) / 2;
    }
    
    hp->size++;
    return ST_OK;
}

RET_STATUS ahp_extract(array_heap *hp, int *ret_value) {
    if (hp == NULL || hp->heap == NULL)
        return ST_FAIL_EMPTY;

    if (hp->size / hp->capacity <= 0.25 && hp->capacity >= 32) {
        // only a quarter of the array is actually used
        // we don't want to shrink past the minimum capacity of 16
        int *new = realloc(hp->heap, sizeof(int) * hp->capacity / 2);
        if (new == NULL)
            return ST_FAIL_MALLOC;
        hp->capacity /= 2;
        hp->heap = new;
    }

    // give the value back before doing the trickle down so that
    // we still give back a valid value even if stuff starts going
    // wrong below
    *ret_value = hp->heap[0];

    // value at extremity
    int data = hp->heap[hp->size-1];
    hp->size--; // decrease the size to signify removing the extremity

    // trickle down
    hp->heap[0] = data;
    
    int current = 0;
    int left_child = (current * 2) + 1;
    int right_child = (current * 2) + 2;

    while (left_child < hp->size) {
        // while haven't reached a leaf
        if (right_child >= hp->size && (hp->type * hp->heap[left_child] < hp->type * hp->heap[current])) {
            swap(&(hp->heap[current]), &(hp->heap[left_child]));
            break;
        }
        else {
            int new_current = hp->type * (hp->heap[left_child]) < hp->type * (hp->heap[right_child]) ? left_child : right_child;

            if (hp->type * hp->heap[current] > hp->type * hp->heap[new_current]) {
                swap(&(hp->heap[current]), &(hp->heap[new_current]));
                current = new_current;
                left_child = (current * 2) + 1;
                right_child = (current * 2) + 2;
                continue;
            }
            break;
        }
    }
    return ST_OK;
}


RET_STATUS ahp_empty(array_heap *hp) {
    if (hp == NULL)
        return ST_FAIL_EMPTY;
    if (hp->size <= 0)
        return ST_FAIL_EMPTY;
    return ST_OK;
}

RET_STATUS ahp_destruct(array_heap *hp) {
    if (hp == NULL)
        return ST_OK;
    free(hp->heap);
    free(hp);
    hp = NULL;
    return ST_OK;
}
