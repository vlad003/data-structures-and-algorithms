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
        BT_NODE *temp = malloc(sizeof(BT_NODE));
        if (temp == NULL)
            return ST_FAIL_MALLOC;
        hp->root = temp;
        hp->extremity = temp;
        done = true;

        return ST_OK;
    }

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
                BT_NODE *temp = malloc(sizeof(BT_NODE));
                if (temp == NULL)
                    return ST_FAIL_MALLOC;

                temp->data = data;
                temp->parent = current;
                temp->left = NULL;
                temp->right = NULL;

                int ext_data = (hp->extremity)->data;
                if (hp->type == min_heap ? temp->data >= ext_data : temp->data <= ext_data)
                    hp->extremity = temp;

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

RET_STATUS hp_extract(HEAP *hp, int *ret_value) {
    if (hp == NULL || hp->root == NULL)
        return ST_FAIL_EMPTY;

    *ret_value = (hp->root)->data;

    // Get the extremity and delete it
    int data = (hp->extremity)->data;


    // Get rid of the node at the extremity

    if (hp->extremity == hp->root) {
        free(hp->extremity);
        hp->extremity = NULL;
        hp->root =  NULL;
        hp->size = 0;
    }
    else {
        BT_NODE *p = (hp->extremity)->parent;
        BT_NODE *c = p->left == hp->extremity ? p->left : p->right;
        
        free(c);
        c = NULL;

        hp->extremity = NULL;
    }

    // trickle down the rest

    bool done = false;
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
                BT_NODE *temp = malloc(sizeof(BT_NODE));
                if (temp == NULL)
                    return ST_FAIL_MALLOC;

                temp->data = data;
                temp->parent = current;
                temp->left = NULL;
                temp->right = NULL;

                int ext_data = (hp->extremity)->data;
                if (hp->type == min_heap ? temp->data >= ext_data : temp->data <= ext_data)
                    hp->extremity = temp;

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
