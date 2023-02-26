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
#include <string.h>

dll_t *dll_new()
{
    dll_t *dll = malloc(sizeof(dll_t));
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

void dll_print(dll_t *self, FILE *fd, char *(*to_string)(void *))
{
    fwrite("[", 1, 2, fd);
    for (dll_node_t *node = self->head; node != NULL; node = node->next)
    {
        char *str = to_string(node->data);
        fwrite(str, 1, strlen(str), fd);
        free(str);
        if (node->next)
        {
            fwrite(", ", 1, 3, fd);
        }
    }
    fwrite("]\n", 1, 3, fd);
}

void *dll_push_back(dll_t *self, void *data)
{
    dll_node_t *node = malloc(sizeof(dll_node_t));
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
    dll_node_t *node = malloc(sizeof(dll_node_t));
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

void *dll_pop_back(dll_t *self)
{
    if (self->tail == NULL)
    {
        fprintf(stderr, "dll_pop_back: list is empty\n");
        return NULL;
    }
    dll_node_t *node = self->tail;
    void *data = node->data;
    self->tail = self->tail->prev;
    if (self->tail)
    {
        self->tail->next = NULL;
    }
    else
    {
        self->head = NULL;
    }
    self->size--;
    free(node);
    return data;
}

void *dll_pop_front(dll_t *self)
{
    if (self->head == NULL)
    {
        fprintf(stderr, "dll_pop_front: list is empty\n");
        return NULL;
    }
    dll_node_t *node = self->head;
    void *data = node->data;
    self->head = self->head->next;
    if (self->head)
    {
        self->head->prev = NULL;
    }
    else
    {
        self->tail = NULL;
    }
    self->size--;
    free(node);
    return data;
}

void *dll_insert(dll_t *self, void *data, size_t index)
{
    if (index > self->size)
    {
        fprintf(stderr, "dll_insert: index out of bounds");
        return NULL;
    }
    if (index == 0)
    {
        return dll_push_front(self, data);
    }
    if (index == self->size)
    {
        return dll_push_back(self, data);
    }
    dll_node_t *node = malloc(sizeof(dll_node_t));
    node->data = data;
    dll_node_t *prev = self->head;
    for (size_t i = 0; i < index - 1; i++)
    {
        prev = prev->next;
    }
    node->next = prev->next;
    node->prev = prev;
    prev->next->prev = node;
    prev->next = node;
    self->size++;
    return data;
}