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
    
    dll_push_back(dll, a);
    dll_push_back(dll, b);

    puts("List:");
    dll_print(dll, stdout, int_to_string);
    fflush(stdout);

    free(dll_pop_front(dll));
    puts("after pop front");
    dll_print(dll, stdout, int_to_string);

    free(dll_pop_back(dll));
    puts("After pop back");
    dll_print(dll, stdout, int_to_string);

    dll_free(dll);

    return 0;
}