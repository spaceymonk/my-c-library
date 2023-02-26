#include "doubly_linked_list.h"

char *int_to_string(void *data)
{
    int *a = data;
    char *str = malloc(10);
    sprintf(str, "%d", *a);
    return str;
}

int int_compare(void *a, void *b)
{
    int *x = a;
    int *y = b;
    return *x - *y;
}

int main()
{

    dll_t *dll = dll_new();

    int *a = (int *)malloc(sizeof(int));
    *a = 1;
    int *b = (int *)malloc(sizeof(int));
    *b = 2;
    int *c = (int *)malloc(sizeof(int));
    *c = 3;
    int *d = (int *)malloc(sizeof(int));
    *d = 4;

    dll_insert_after(dll, dll->head, a);
    dll_insert_after(dll, dll->head, b);
    dll_insert_after(dll, dll->head, c);
    dll_insert_after(dll, dll->head, d);
    dll_print(dll, stdout, int_to_string);
    fflush(stdout);

    dll_sort(dll, int_compare);
    dll_print(dll, stdout, int_to_string);
    fflush(stdout);

    int f = 2;
    dll_node_t *found = dll_search(dll, &f, int_compare);
    if (found)
    {
        dll_remove(dll, found);
    }
    else
    {
        printf("Not found\n");
    }
    dll_print(dll, stdout, int_to_string);


    free(a);
    free(b);
    free(c);
    free(d);
    dll_clear(dll, NULL);
    dll_free(dll);

    return 0;
}