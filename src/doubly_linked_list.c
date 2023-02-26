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

#include "doubly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

dll_t *dll_new()
{
    dll_t *dll = (dll_t *)malloc(sizeof(dll_t));
    dll->head = NULL;
    dll->tail = NULL;
    dll->size = 0;
    return dll;
}

int dll_free(dll_t *dll)
{
    if (dll->size == 0)
    {
        free(dll);
        return 0;
    }
    fprintf(stderr, "dll_free: dll is not empty\n");
    return 1;
}

void *dll_push_back(dll_t *self, void *data)
{
    dll_node_t *node = (dll_node_t *)malloc(sizeof(dll_node_t));
    node->data = data;
    node->next = NULL;
    node->prev = self->tail;
    if (self->tail)
    {
        self->tail->next = node;
    }
    self->tail = node;
    if (self->head == NULL)
    {
        self->head = node;
    }
    self->size++;
    return data;
}

void *dll_push_front(dll_t *self, void *data)
{
    dll_node_t *node = (dll_node_t *)malloc(sizeof(dll_node_t));
    node->data = data;
    node->next = self->head;
    node->prev = NULL;
    if (self->head)
    {
        self->head->prev = node;
    }
    self->head = node;
    if (self->tail == NULL)
    {
        self->tail = node;
    }
    self->size++;
    return data;
}