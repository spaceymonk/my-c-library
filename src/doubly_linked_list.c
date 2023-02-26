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
    fprintf(stderr, "dll_free: list is not empty\n");
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

dll_node_t *dll_insert_after(dll_t *self, dll_node_t *node, void *data)
{
    if (node == NULL)
    {
        if (self->size == 0)
        {
            return dll_push_back(self, data);
        }
        fprintf(stderr, "dll_insert_after: node is NULL");
        return NULL;
    }

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    new_node->data = data;
    new_node->next = node->next;
    new_node->prev = node;
    if (node->next)
    {
        node->next->prev = new_node;
    }
    else
    {
        self->tail = new_node;
    }
    node->next = new_node;
    self->size++;
    return new_node;
}

dll_node_t *dll_insert_before(dll_t *self, dll_node_t *node, void *data)
{
    if (node == NULL)
    {
        if (self->size == 0)
        {
            return dll_push_front(self, data);
        }
        fprintf(stderr, "dll_insert_before: node is NULL");
        return NULL;
    }

    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    new_node->data = data;
    new_node->next = node;
    new_node->prev = node->prev;
    if (node->prev)
    {
        node->prev->next = new_node;
    }
    else
    {
        self->head = new_node;
    }
    node->prev = new_node;
    self->size++;
    return new_node;
}

void *dll_remove(dll_t *self, dll_node_t *node)
{
    if (node == NULL)
    {
        fprintf(stderr, "dll_remove: node is NULL");
        return NULL;
    }
    if (self->size == 0)
    {
        fprintf(stderr, "dll_remove: list is empty");
        return NULL;
    }
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        self->head = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        self->tail = node->prev;
    }
    void *data = node->data;
    free(node);
    self->size--;
    return data;
}

dll_node_t *dll_search(dll_t *self, void *data, int (*cmp)(void *, void *))
{
    dll_node_t *node = self->head;
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

void dll_clear(dll_t *self, void (*free_handler)(void *))
{
    if (free_handler == NULL)
    {
        dll_node_t *node = self->head;
        while (node != NULL)
        {
            dll_node_t *next = node->next;
            free(node);
            node = next;
        }
    }
    else
    {
        dll_node_t *node = self->head;
        while (node != NULL)
        {
            dll_node_t *next = node->next;
            free_handler(node->data);
            free(node);
            node = next;
        }
    }
    self->size = 0;
}