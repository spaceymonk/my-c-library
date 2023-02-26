#include "doubly_linked_list.h"

char *int_to_string(void *data)
{
    int *a = data;
    char *str = malloc(10);
    sprintf(str, "%d", *a);
    return str;
}

int main()
{

    dll_t *dll = dll_new();

    int *a = (int *)malloc(sizeof(int));
    *a = 1;
    int *b = (int *)malloc(sizeof(int));
    *b = 2;

    dll_insert(dll, a, 0);
    dll_insert(dll, b, 0);
    dll_insert(dll, b, 0);
    dll_insert(dll, b, 0);

    dll_print(dll, stdout, int_to_string);

    dll_remove(dll, 1);
    dll_print(dll, stdout, int_to_string);

    dll_remove(dll, 1);
    dll_print(dll, stdout, int_to_string);

    dll_remove(dll, 1);
    dll_print(dll, stdout, int_to_string);

    free(a);
    free(b);
    dll_clear(dll, NULL);
    dll_free(dll);

    return 0;
}