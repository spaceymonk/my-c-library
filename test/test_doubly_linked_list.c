#include <assert.h>
#include "doubly_linked_list.h"

int int_cmp(void *a, void *b)
{
    if (a == NULL || b == NULL)
    {
        return 1;
    }
    return *(int *)a - *(int *)b;
}

dll_t *test_new()
{
    dll_t *dll = dll_new();
    assert(dll != NULL);
    assert(dll->head == NULL);
    assert(dll->tail == NULL);
    assert(dll->size == 0);
    return dll;
}

void test_clear(dll_t *dll)
{
    dll_clear(dll, NULL);
    assert(dll->head == NULL);
    assert(dll->tail == NULL);
    assert(dll->size == 0);
}

void test_push_back_one_element(dll_t *dll, int *value)
{
    dll_node_t *expected_head = dll->head;
    dll_node_t *prev_tail = dll->tail;
    size_t expected_size = dll->size + 1;

    int x = *(int *)dll_push_back(dll, value);
    assert(x == *value);
    if (expected_size != 1)
    {
        assert(dll->head == expected_head);
        assert(dll->tail->prev == prev_tail);
    }
    assert(dll->size == expected_size);
}

void test_push_front_one_element(dll_t *dll, int *value)
{
    dll_node_t *expected_tail = dll->tail;
    dll_node_t *prev_head = dll->head;
    size_t expected_size = dll->size + 1;

    int x = *(int *)dll_push_front(dll, value);
    assert(x == *value);
    if (expected_size != 1)
    {
        assert(dll->tail == expected_tail);
        assert(dll->head->next == prev_head);
    }
    assert(dll->size == expected_size);
}

void test_pop_back_one_element(dll_t *dll, int expected)
{
    dll_node_t *expected_head = dll->head;
    dll_node_t *expected_tail = dll->tail->prev;
    size_t expected_size = dll->size - 1;

    int x = *(int *)dll_pop_back(dll);
    assert(x == expected);
    if (expected_size != 0)
    {
        assert(dll->head == expected_head);
        assert(dll->tail == expected_tail);
    }
    assert(dll->size == expected_size);
}

void test_pop_front_one_element(dll_t *dll, int expected)
{
    dll_node_t *expected_head = dll->head->next;
    dll_node_t *expected_tail = dll->tail;
    size_t expected_size = dll->size - 1;

    int x = *(int *)dll_pop_front(dll);
    assert(x == expected);
    if (expected_size != 0)
    {
        assert(dll->head == expected_head);
        assert(dll->tail == expected_tail);
    }
    assert(dll->size == expected_size);
}

void test_search(dll_t *dll, int *value, void *expected)
{
    dll_node_t *actual = dll_search(dll, value, int_cmp);
    if (actual != NULL)
    {
        assert(actual->data == expected);
    }
    else
    {
        assert(expected == NULL);
    }
}

int main()
{
    dll_t *dll = test_new();
    int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int f = 42;

    for (int i = 0; i < 10; i++)
    {
        test_push_back_one_element(dll, &values[i]);
    }
    test_search(dll, &values[1], &values[1]);
    test_search(dll, &f, NULL);

    for (int i = 0; i < 10; i++)
    {
        test_pop_back_one_element(dll, values[9 - i]);
    }

    for (int i = 0; i < 10; i++)
    {
        test_push_front_one_element(dll, &values[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        test_pop_front_one_element(dll, values[9 - i]);
    }

    test_clear(dll);
    dll_free(dll);

    puts("All tests passed!");
    return 0;
}