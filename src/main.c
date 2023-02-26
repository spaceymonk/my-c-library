#include "../include/doubly_linked_list.h"

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

    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int f = 2;

    dll_insert_after(dll, dll->head, &a);
    dll_insert_after(dll, dll->head, &b);
    dll_insert_after(dll, dll->head, &c);
    dll_insert_after(dll, dll->head, &d);
    dll_print(dll, stdout, int_to_string);
    fflush(stdout);

    dll_sort(dll, int_compare);
    dll_reverse(dll);
    dll_print(dll, stdout, int_to_string);
    fflush(stdout);

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

    dll_clear(dll, NULL);
    dll_free(dll);

    return 0;
}