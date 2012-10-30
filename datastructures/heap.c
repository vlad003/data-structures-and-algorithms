#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"

RET_STATUS hp_empty(HEAP *hp) {
    if (hp == NULL)
        return ST_FAIL_EMPTY;
    else if (hp->size <= 0)
        return ST_OK;
    return ST_FAIL_EMPTY;
}

RET_STATUS hp_insert(HEAP *hp, int data) {
    if (hp == NULL)
        return ST_FAIL_EMPTY;

    // trickle down
    
    bool done = false;

    if (hp->root == NULL) {
        hp->root = temp;
        hp->extremity = temp;
        done = true;
    }

    if (!done)
        BT_NODE *current = hp->root;

    while (!done) {
        // if it's a min_heap, we trickle the node down if it's less than current value
        if (hp->type == min_heap ? current->data <= data : current->data >= data) {
            current->data ^= data;
            data ^= current->data;
            current->data ^= data;

            if ((current->left == NULL) != (current->right == NULL))
                current = current->left != NULL ? current->left : current->right;
            else if (current->left == NULL && current->right == NULL) {
                // reached a leaf
                if ((BT_NODE *temp = malloc(sizeof(BT_NODE))) == NULL)
                    return ST_FAIL_MALLOC;

                temp->data = data;
                temp->parent = current;
                temp->left = NULL;
                temp->right = NULL;

                break;
            }
            else 
                current = (current->left)->data < (current->right)->data ? current->left : current->right;
        }
        else
            break;
    }

    return ST_OK;
}


