#include "doubly_linked_list.h"
#include "dynamic_array.h"

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

    da_t *da = da_new(10);

    int a = -1;
    int b = 2;
    int c = 3;
    int d = 4;
    // int f = 3;

    da_push_back(da, &d);
    da_push_back(da, &c);
    da_push_back(da, &b);
    da_push_back(da, &a);

    da_print(da, stdout, int_to_string);
    da_sort(da, int_compare);
    da_print(da, stdout, int_to_string);
    fflush(stdout);

    // int x = -1;
    // int r = da_binary_search(da, &x, int_compare);
    // printf("r = %d\n", r);

    // size_t x = da_search(da, &f, int_compare);
    // printf("x = %zu\n", x);

    // da_remove(da, x);
    // da_print(da, stdout, int_to_string);
    // fflush(stdout);

    da_clear(da, NULL);
    da_free(da);

    return 0;
}