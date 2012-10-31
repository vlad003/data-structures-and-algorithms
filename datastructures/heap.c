#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

void swap(int *x, int *y) {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
}

RET_STATUS hp_empty(HEAP *hp) {
    if (hp == NULL)
        return ST_FAIL_EMPTY;
    else if (hp->size <= 0)
        return ST_FAIL_EMPTY;
    return ST_OK;
}

RET_STATUS hp_insert(HEAP *hp, int data) {
    if (hp == NULL)
        return ST_FAIL_EMPTY;

    // trickle down

    bool done = false;

    BT_NODE *temp = malloc(sizeof(BT_NODE));
    if (temp == NULL)
        return ST_FAIL_MALLOC;
    temp->data = data;
    temp->parent = NULL;
    temp->left = NULL;
    temp->right = NULL;

    if (hp->root == NULL) {
        hp->root = temp;
        hp->extremity = temp;
        done = true;

        hp->size++;
        return ST_OK;
    }
    else if (hp->extremity == hp->root) {
        temp->parent = hp->root;
        (hp->root)->left = temp;
    }
    else if (hp->size < 4) {
        // this is the case we can't do the stuff with ext->parent->parent
        // because there isn't two levels of parents
        switch (hp->size) {
            case 2:
                temp->parent = hp->root;
                (hp->root)->right = temp;
                break;
            case 3:
                temp->parent = (hp->root)->left;
                ((hp->root)->left)->left = temp;
                break;
            default:
                return ST_FAIL;
        }
    }
    else {
        // stick the node where the next one should sit at the bottom
        if (((hp->extremity)->parent)->left == hp->extremity) {
            // current is the left child of its parent
            temp->parent = (hp->extremity)->parent;
            ((hp->extremity)->parent)->right = temp;
        }
        else if ((((hp->extremity)->parent)->parent)->right == (hp->extremity)->parent) {
            // extremity is the rightmost node on a full row,
            // so we need to move to the next row.
            BT_NODE *current = hp->root;
            while (current->left != NULL)
                current = current->left;

            temp->parent = current;
            current->left = temp;
        }
        else {
            // extremity is the right child of parent, but there's still space on the row
            temp->parent = (((hp->extremity)->parent)->parent)->right;
            ((((hp->extremity)->parent)->parent)->right)->left = temp;
        }
    }

    // new node is the new extremity.
    // we didn't update till now so we could use the old value above
    hp->extremity = temp;

    // trickle the value up
    BT_NODE *current = hp->extremity;

    while (current->parent != NULL && (hp->type * current->data < hp->type * (current->parent)->data)) {
        // while the value of current < value of parent, swap them (for min_type)
        swap(&(current->data), &((current->parent)->data));

        current = current->parent;
    }
    hp->size++;
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
        // extremity is the same as the root
        // so we need to clear the heap
        free(hp->root);
        hp->root = NULL;
        hp->extremity = NULL;
        hp->size = 0;
        return ST_OK; // We don't want to try to go down another level
    }
    else if (hp->size < 4) {
        // in the else, we use ext->parent->parent, which we can't do
        // if size < 4
        BT_NODE *old_ext = hp->extremity;

        switch (hp->size) {
            case 2:
                hp->extremity = hp->root;
                break;
            case 3:
                hp->extremity = ((old_ext)->parent)->left;
                break;
            default:
                break;
        }
        free(old_ext);
    }
    else {
        if (hp->extremity == NULL)
            return ST_FAIL;
        
        // update the hp->extremity pointer before deleting it
        BT_NODE *old_ext = hp->extremity;

        if (((old_ext->parent)->parent)->right == (old_ext->parent)) {
            // extremity is the rightmost node of a full row
            hp->extremity = (old_ext->parent)->left;
        }
        else if ((old_ext->parent)->right == NULL) {
            // extremity is the only node on a row and it's the leftmost one
            BT_NODE *current = hp->root;
            while (current->right != NULL)
                current = current->right;

            hp->extremity = current;
        }
        else {
            // extremity is the right child of a node somewhere else
            hp->extremity = (old_ext->parent)->left;
        }

        // delete the old extremity node
        BT_NODE *p = (old_ext)->parent;
        // set the left/right pointers to NULL when removing
        // the extremity.
        if (p->left == old_ext)
            p->left = NULL;
        else if (p->right == old_ext)
            p->right = NULL;
        else
            // should never get here
            return ST_FAIL;

        free(old_ext);
    }

    // trickle down the rest

    BT_NODE *current = hp->root;
    (hp->root)->data = data;

    while (current->left != NULL && current->right != NULL) {
        // while haven't reached a leaf
        if (current->right == NULL && (hp->type * (current->left)->data < hp->type * current->data)) {
            swap(&(current->data), &((current->left)->data));
            break;
        }
        else {
            BT_NODE *new_curr = hp->type * (current->left)->data < hp->type * (current->right)->data ? current->left : current->right;

            if (hp->type * current->data > hp->type * new_curr->data) {
                swap(&(current->data), &(new_curr->data));
                current = new_curr;
                continue;
            }
            break;
        }
    }
    hp->size--;
    return ST_OK;
}
