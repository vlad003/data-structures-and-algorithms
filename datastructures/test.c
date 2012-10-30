#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dlinkedlist.h"

int main() {
    DLINKEDLIST *dll = malloc(sizeof(DLINKEDLIST));

    // create new
    
    dll->begin = NULL;
    dll->end = NULL;
    dll->size = 0;

    while (!empty(dll)) 
        printf("%d ", pop(dll));

    puts("\ninserting");

    for (int x = 1; x <= 6; ++x) {
        append(dll, x);
    }

    insert(dll, 2, 7);
    puts("\nhere");
    printf("begin: %d\n", dll->begin);
    insert(dll, 0, 8);
    puts("\nhere");
    printf("begin: %d\n", dll->begin);
    insert(dll, -10, 99);
    puts("\nhere");
    printf("begin: %d\n", dll->begin);
    insert(dll, 500, 193);
    puts("\nhere");

    printf("begin: %d\n", dll->begin);
    printf("end: %d\n", dll->end);

    while (!empty(dll)) {
        printf("%d-", dll->size);
        printf("%d ", pop(dll));
        printf("%d\n", dll->begin);
    }


    putchar('\n');
    return 0;
}
