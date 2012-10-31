#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

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

    if (hp->root == NULL) {
        BT_NODE *temp = malloc(sizeof(BT_NODE));
        if (temp == NULL)
            return ST_FAIL_MALLOC;
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        hp->root = temp;
        hp->extremity = temp;
        done = true;

        hp->size++;
        return ST_OK;
    }

    BT_NODE *current = hp->root;

    while (!done) {
        // if it's a min_heap, we trickle the node down if it's less than current value
        if (hp->type * current->data >= hp->type * data) {
            current->data ^= data;
            data ^= current->data;
            current->data ^= data;
        }
        if ((current->left == NULL) != (current->right == NULL)) {
            // one of the branches is null
            current = current->left != NULL ? current->left : current->right;
            if (hp->type * current->data >= hp->type * data) {
                continue;
            }
            else {
                // if we don't need to go down another level, we need to
                // put the value on the NULL branch

                BT_NODE *temp = malloc(sizeof(BT_NODE));
                if (temp == NULL)
                    return ST_FAIL_MALLOC;

                temp->data = data;
                temp->parent = current->parent;
                temp->left = NULL;
                temp->right = NULL;

                (current->parent)->right = temp; // it will ALWAYS be the right one;
                if (hp->extremity == NULL)
                    hp->extremity = temp;
                else {
                    int ext_data = (hp->extremity)->data;
                    if (hp->type * ext_data <= hp->type * data)
                        hp->extremity = temp;
                }
                break;
            }

        }
        else if (current->left == NULL && current->right == NULL) {
            // reached a leaf
            BT_NODE *temp = malloc(sizeof(BT_NODE));
            if (temp == NULL)
                return ST_FAIL_MALLOC;

            temp->data = data;
            temp->parent = current;
            temp->left = NULL;
            temp->right = NULL;

            current->left = temp; // it must ALWAYS be the left one;

            if (hp->extremity == NULL)
                hp->extremity = temp;
            else {
                if 

                int ext_data = (hp->extremity)->data;
                if (hp->type * ext_data <= hp->type * data)
                    hp->extremity = temp;
            }

            break;
        }
        else { 
            current = (current->left)->data < (current->right)->data ? current->left : current->right;
        }
    }
    hp->size++;
    return ST_OK;
}

RET_STATUS hp_extract(HEAP *hp, int *ret_value) {
    if (hp == NULL || hp->root == NULL)
        return ST_FAIL_EMPTY;

    printf("root at top = %d\n", hp->root);
    *ret_value = (hp->root)->data;
    printf("ret_value = %d\n", *ret_value);

    // Get the extremity and delete it
    int data = (hp->extremity)->data;
    printf("extremity data = %d\n", data);


    // Get rid of the node at the extremity

    if (hp->extremity == hp->root) {
        // extremity is the same as the root
        // so we need to clear the heap
        puts("\n extremity is root");
        free(hp->root);
        hp->root = NULL;
        hp->extremity = NULL;
        hp->size = 0;
        return ST_OK; // We don't want to try to go down another level
    }
    else {
        puts("\n hp->size != 1");
        if (hp->extremity == NULL)
            return ST_FAIL;
        BT_NODE *p = (hp->extremity)->parent;
        printf("\n &extremity parent = %d\t%d\n", p, p->data);
        
        if (p->left == hp->extremity)
            p->left = NULL;
        else if (p->right == hp->extremity)
            p->right = NULL;
        else
            // should never get here
            puts("\nWHAT'RE WE DOING HERE?");

        printf("left child = %d", p->left);
        if (p->left != NULL)
            printf("\t%d", (p->left)->data);
        printf("\n");
        printf("right child = %d", p->right);
        if (p->right != NULL)
            printf("\t%d", (p->right)->data);
        printf("\n");

        free(hp->extremity);
        hp->extremity = NULL;
        hp->size--;
    }

    // trickle down the rest

    bool done = false;
    bool extremity_set = false;

    BT_NODE *current = hp->root;

    // move the smaller child into the parent and move to the smaller child
    // if current->data < data, move into smaller child and repeat
    // if current->data >= data, stick data into current->data and be done
    // no need to add new nodes in this case.
    //
    //
    (hp->root)->data = data;
    while (!done) {
        // if it's a min_heap, we trickle the node down if it's less than current value

        if ((current->left == NULL) != (current->right == NULL)) {
            // one of the branches is null
            // so we stick the extremity in that branch.
            // We could start moving stuff around, but why would we?
            
            // The NULL branch will always be the right one.
            BT_NODE *temp = malloc(sizeof(BT_NODE));
            if (temp == NULL)
                return ST_FAIL_MALLOC;

            temp->data = data;
            temp->parent = current;
            temp->left = NULL;
            temp->right = NULL;

            current->right = temp;

            hp->extremity = temp;
            extremity_set = true;

            // if null was there, then that means that that's were the extremity
            // was removed from. So the other side has a blank node that we need to bring other
            // values up into

            current = (current->parent)->left;
        }
        else if (current->left == NULL && current->right == NULL) {
            // we've reached the last node on a path
            // meaning we already dragged its data up, and need to
            // put the extremity here;
            (current->parent)->data = current->data;
            current->data = data;
            hp->extremity = current;
            break;
        }
        else { 
            // we're at an inner node
            current = hp->type * (current->left)->data <= hp->type * (current->right)->data ? current->left : current->right;
            /*(current->parent)->data = current->data;*/
        }
    }
    return ST_OK;
}
