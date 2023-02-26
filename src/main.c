#include "doubly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{

    dll_t *dll = dll_new();

    int *a = (int *)malloc(sizeof(int));
    *a = 1;
    int *b = (int *)malloc(sizeof(int));
    *b = 2;
    
    dll_push_back(dll, a);
    dll_push_back(dll, b);

    for (dll_node_t *node = dll->head; node != NULL; node = node->next)
    {
        printf("%d\n", *((int*)node->data));
    }

    dll_free(dll);

    return 0;
}