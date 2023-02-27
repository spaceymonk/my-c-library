/**
 * @file doubly_linked_list.c
 * @author Berktug K. Ozkan (@spaceymonk)
 * @brief Doubly Linked List implementation
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/doubly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dll_t *dll_new()
{
    dll_t *dll = malloc(sizeof(dll_t));
    if (dll == NULL)
    {
        fprintf(stderr, "dll_new: malloc failed\n");
        return NULL;
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return dll;
}

int dll_free(dll_t *dll)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_free: dll is NULL\n");
        return -1;
    }
    if (dll->size != 0)
    {
        fprintf(stderr, "dll_free: list is dirty\n");
        return -1;
    }
    free(dll);
    return 0;
}

size_t dll_size(dll_t *dll)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_size: dll is NULL\n");
        return -1;
    }
    return dll->size;
}

int dll_print(dll_t *dll, FILE *fd, char *(*to_string)(void *))
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_print: dll is NULL\n");
        return -1;
    }
    if (fd == NULL)
    {
        fprintf(stderr, "dll_print: fd is NULL\n");
        return -1;
    }
    if (to_string == NULL)
    {
        fprintf(stderr, "dll_print: to_string is NULL\n");
        return -1;
    }
    size_t written_bytes = fwrite("[", 1, 1, fd);
    if (written_bytes != 1)
    {
        fprintf(stderr, "dll_print: fwrite failed\n");
        return -1;
    }
    for (dll_node_t *node = dll->head; node != NULL; node = node->next)
    {
        char *str = to_string(node->data);
        written_bytes = fwrite(str, 1, strlen(str), fd);
        if (written_bytes != strlen(str))
        {
            fprintf(stderr, "dll_print: fwrite failed\n");
            return -1;
        }
        free(str);
        if (node->next)
        {
            written_bytes = fwrite(", ", 1, 2, fd);
            if (written_bytes != 2)
            {
                fprintf(stderr, "dll_print: fwrite failed\n");
                return -1;
            }
        }
    }
    written_bytes = fwrite("]\n", 1, 2, fd);
    if (written_bytes != 2)
    {
        fprintf(stderr, "dll_print: fwrite failed\n");
        return -1;
    }
    return 0;
}

void *dll_push_back(dll_t *dll, void *data)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_push_back: dll is NULL\n");
        return NULL;
    }
    dll_node_t *node = malloc(sizeof(dll_node_t));
    if (node == NULL)
    {
        fprintf(stderr, "dll_push_back: malloc failed\n");
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    node->prev = dll->tail;
    if (dll->tail)
    {
        dll->tail->next = node;
    }
    dll->tail = node;
    if (dll->head == NULL)
    {
        dll->head = node;
    }
    dll->size++;
    return data;
}

void *dll_push_front(dll_t *dll, void *data)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_push_front: dll is NULL\n");
        return NULL;
    }
    dll_node_t *node = malloc(sizeof(dll_node_t));
    if (node == NULL)
    {
        fprintf(stderr, "dll_push_front: malloc failed\n");
        return NULL;
    }
    node->data = data;
    node->next = dll->head;
    node->prev = NULL;
    if (dll->head)
    {
        dll->head->prev = node;
    }
    dll->head = node;
    if (dll->tail == NULL)
    {
        dll->tail = node;
    }
    dll->size++;
    return data;
}

void *dll_pop_back(dll_t *dll)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_pop_back: dll is NULL\n");
        return NULL;
    }
    if (dll->tail == NULL)
    {
        fprintf(stderr, "dll_pop_back: list is empty\n");
        return NULL;
    }
    dll_node_t *node = dll->tail;
    void *data = node->data;
    dll->tail = dll->tail->prev;
    if (dll->tail)
    {
        dll->tail->next = NULL;
    }
    else
    {
        dll->head = NULL;
    }
    dll->size--;
    free(node);
    return data;
}

void *dll_pop_front(dll_t *dll)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_pop_front: dll is NULL\n");
        return NULL;
    }
    if (dll->head == NULL)
    {
        fprintf(stderr, "dll_pop_front: list is empty\n");
        return NULL;
    }
    dll_node_t *node = dll->head;
    void *data = node->data;
    dll->head = dll->head->next;
    if (dll->head)
    {
        dll->head->prev = NULL;
    }
    else
    {
        dll->tail = NULL;
    }
    dll->size--;
    free(node);
    return data;
}

dll_node_t *dll_insert_after(dll_t *dll, dll_node_t *node, void *data)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_insert_after: dll is NULL\n");
        return NULL;
    }
    if (node == NULL)
    {
        if (dll->size == 0)
        {
            return dll_push_back(dll, data);
        }
        fprintf(stderr, "dll_insert_after: node is NULL\n");
        return NULL;
    }

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "dll_insert_after: malloc failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = node->next;
    new_node->prev = node;
    if (node->next)
    {
        node->next->prev = new_node;
    }
    else
    {
        dll->tail = new_node;
    }
    node->next = new_node;
    dll->size++;
    return new_node;
}

dll_node_t *dll_insert_before(dll_t *dll, dll_node_t *node, void *data)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_insert_before: dll is NULL\n");
        return NULL;
    }
    if (node == NULL)
    {
        if (dll->size == 0)
        {
            return dll_push_front(dll, data);
        }
        fprintf(stderr, "dll_insert_before: node is NULL\n");
        return NULL;
    }

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "dll_insert_before: malloc failed\n");
        return NULL;
    }
    new_node->data = data;
    new_node->next = node;
    new_node->prev = node->prev;
    if (node->prev)
    {
        node->prev->next = new_node;
    }
    else
    {
        dll->head = new_node;
    }
    node->prev = new_node;
    dll->size++;
    return new_node;
}

void *dll_remove(dll_t *dll, dll_node_t *node)
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_remove: dll is NULL\n");
        return NULL;
    }
    if (node == NULL)
    {
        fprintf(stderr, "dll_remove: node is NULL\n");
        return NULL;
    }
    if (dll->size == 0)
    {
        fprintf(stderr, "dll_remove: list is empty\n");
        return NULL;
    }
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        dll->head = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        dll->tail = node->prev;
    }
    void *data = node->data;
    free(node);
    dll->size--;
    return data;
}

dll_node_t *dll_search(dll_t *dll, void *data, int (*cmp)(void *, void *))
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_search: dll is NULL\n");
        return NULL;
    }
    if (cmp == NULL)
    {
        fprintf(stderr, "dll_search: cmp is NULL\n");
        return NULL;
    }
    dll_node_t *node = dll->head;
    while (node != NULL)
    {
        if (cmp(node->data, data) == 0)
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

int dll_clear(dll_t *dll, void (*free_handler)(void *))
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_clear: dll is NULL\n");
        return -1;
    }
    if (free_handler == NULL)
    {
        dll_node_t *node = dll->head;
        while (node != NULL)
        {
            dll_node_t *next = node->next;
            free(node);
            node = next;
        }
    }
    else
    {
        dll_node_t *node = dll->head;
        while (node != NULL)
        {
            dll_node_t *next = node->next;
            free_handler(node->data);
            free(node);
            node = next;
        }
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return 0;
}

dll_t *dll_reverse(dll_t *dll)
{
    if (dll->size <= 1)
    {
        return dll;
    }
    dll_node_t *node = dll->head;
    while (node != NULL)
    {
        dll_node_t *tmp = node->next;
        node->next = node->prev;
        node->prev = tmp;
        node = tmp;
    }
    node = dll->head;
    dll->head = dll->tail;
    dll->tail = node;
    return dll;
}

dll_t *dll_sort(dll_t *dll, int (*cmp)(void *, void *))
{
    if (dll == NULL)
    {
        fprintf(stderr, "dll_sort: dll is NULL\n");
        return NULL;
    }
    if (dll->size == 0)
    {
        return dll;
    }
    dll->head = __dll_sort(dll->head, cmp);
    dll->tail = dll->head;
    while (dll->tail->next != NULL)
    {
        dll->tail = dll->tail->next;
    }
    return dll;
}

dll_node_t *__dll_get_middle_node(dll_node_t *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    dll_node_t *slow = head;
    dll_node_t *fast = head;
    while (fast->next != NULL && fast->next->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

dll_node_t *__dll_merge(dll_node_t *head1, dll_node_t *head2, int (*cmp)(void *, void *))
{
    if (head1 == NULL)
    {
        return head2;
    }
    if (head2 == NULL)
    {
        return head1;
    }
    if (cmp(head1->data, head2->data) < 0)
    {
        head1->next = __dll_merge(head1->next, head2, cmp);
        head1->next->prev = head1;
        head1->prev = NULL;
        return head1;
    }
    head2->next = __dll_merge(head1, head2->next, cmp);
    head2->next->prev = head2;
    head2->prev = NULL;
    return head2;
}

dll_node_t *__dll_sort(dll_node_t *head, int (*cmp)(void *, void *))
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    dll_node_t *middle = __dll_get_middle_node(head);
    dll_node_t *next_of_middle = middle->next;
    middle->next = NULL;
    dll_node_t *left = __dll_sort(head, cmp);
    dll_node_t *right = __dll_sort(next_of_middle, cmp);
    dll_node_t *sorted_list = __dll_merge(left, right, cmp);
    return sorted_list;
}