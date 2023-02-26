#include "../include/dynamic_array.h"

#include <string.h>

da_t *da_new(size_t capacity)
{
    da_t *da = malloc(sizeof(da_t));
    if (da == NULL)
    {
        fprintf(stderr, "da_new: malloc failed\n");
        return NULL;
    }
    da->capacity = capacity;
    da->size = 0;
    da->array = malloc(sizeof(void *) * capacity);
    if (da->array == NULL)
    {
        fprintf(stderr, "da_new: malloc failed\n");
        free(da);
        return NULL;
    }
    return da;
}

int da_free(da_t *self)
{
    if (self == NULL)
    {
        fprintf(stderr, "da_free: given parameter is NULL\n");
        return -1;
    }
    if (self->size > 0)
    {
        fprintf(stderr, "da_free: array is not empty\n");
        return -1;
    }
    free(self->array);
    free(self);
    return 0;
}

void *da_push_back(da_t *self, void *data)
{
    if (self == NULL)
    {
        fprintf(stderr, "da_push_back: given parameter is NULL\n");
        return NULL;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_push_back: array is NULL\n");
        return NULL;
    }
    if (self->size == self->capacity)
    {
        self->capacity *= 2;
        self->array = realloc(self->array, sizeof(void *) * self->capacity);
        if (self->array == NULL)
        {
            fprintf(stderr, "da_push_back: realloc failed\n");
            return NULL;
        }
    }
    self->array[self->size] = data;
    self->size++;
    return data;
}

void *da_set(da_t *self, size_t index, void *data)
{
    if (self == NULL)
    {
        fprintf(stderr, "da_set: given parameter is NULL\n");
        return NULL;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_set: array is NULL\n");
        return NULL;
    }
    if (index >= self->size)
    {
        fprintf(stderr, "da_set: index out of bounds\n");
        return NULL;
    }
    self->array[index] = data;
    return data;
}

void *da_get(da_t *self, size_t index)
{
    if (self == NULL)
    {
        fprintf(stderr, "da_get: given parameter is NULL\n");
        return NULL;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_get: array is NULL\n");
        return NULL;
    }
    if (index >= self->size)
    {
        fprintf(stderr, "da_get: index out of bounds\n");
        return NULL;
    }
    return self->array[index];
}

void *da_remove(da_t *self, size_t index)
{
    if (self == NULL)
    {
        fprintf(stderr, "da_remove: given parameter is NULL\n");
        return NULL;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_remove: array is NULL\n");
        return NULL;
    }
    if (index >= self->size)
    {
        fprintf(stderr, "da_remove: index out of bounds\n");
        return NULL;
    }
    void *data = self->array[index];
    for (size_t i = index; i < self->size - 1; i++)
    {
        self->array[i] = self->array[i + 1];
    }
    self->size--;
    return data;
}

int da_clear(da_t *self, void (*free_handler)(void *))
{
    if (self == NULL)
    {
        fprintf(stderr, "da_clear: given parameter is NULL\n");
        return -1;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_clear: array is NULL\n");
        return -1;
    }
    if (free_handler != NULL)
    {
        for (size_t i = 0; i < self->size; i++)
        {
            free_handler(self->array[i]);
        }
    }
    self->size = 0;
    return 0;
}

void *da_insert(da_t *self, size_t index, void *data)
{
    if (self == NULL)
    {
        fprintf(stderr, "da_insert: given parameter is NULL\n");
        return NULL;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_insert: array is NULL\n");
        return NULL;
    }
    if (index > self->size)
    {
        fprintf(stderr, "da_insert: index out of bounds\n");
        return NULL;
    }
    if (self->size == self->capacity)
    {
        self->capacity *= 2;
        self->array = realloc(self->array, sizeof(void *) * self->capacity);
        if (self->array == NULL)
        {
            fprintf(stderr, "da_insert: realloc failed\n");
            return NULL;
        }
    }
    for (size_t i = self->size; i > index; i--)
    {
        self->array[i] = self->array[i - 1];
    }
    self->array[index] = data;
    self->size++;
    return data;
}

size_t da_search(da_t *self, void *data, int (*cmp)(void *, void *))
{
    if (self == NULL)
    {
        fprintf(stderr, "da_search: given parameter is NULL\n");
        return -1;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_search: array is NULL\n");
        return -1;
    }
    if (cmp == NULL)
    {
        fprintf(stderr, "da_search: cmp is NULL\n");
        return -1;
    }
    for (size_t i = 0; i < self->size; i++)
    {
        if (cmp(self->array[i], data) == 0)
        {
            return i;
        }
    }
    return -1;
}

int da_print(da_t *self, FILE *fd, char *(*to_string)(void *))
{
    if (self == NULL)
    {
        fprintf(stderr, "da_print: given parameter is NULL\n");
        return -1;
    }
    if (self->array == NULL)
    {
        fprintf(stderr, "da_print: array is NULL\n");
        return -1;
    }
    if (fd == NULL)
    {
        fprintf(stderr, "da_print: fd is NULL\n");
        return -1;
    }
    if (to_string == NULL)
    {
        fprintf(stderr, "da_print: to_string is NULL\n");
        return -1;
    }
    size_t written_bytes = fwrite("[", 1, 1, fd);
    if (written_bytes != 1)
    {
        fprintf(stderr, "da_print: fwrite failed\n");
        return -1;
    }
    for (size_t i = 0; i < self->size; i++)
    {
        char *str = to_string(self->array[i]);
        written_bytes = fwrite(str, 1, strlen(str), fd);
        if (written_bytes != strlen(str))
        {
            fprintf(stderr, "da_print: fwrite failed\n");
            return -1;
        }
        free(str);
        if (i < self->size - 1)
        {
            written_bytes = fwrite(", ", 1, 2, fd);
            if (written_bytes != 2)
            {
                fprintf(stderr, "da_print: fwrite failed\n");
                return -1;
            }
        }
    }
    written_bytes = fwrite("]\n", 1, 2, fd);
    if (written_bytes != 2)
    {
        fprintf(stderr, "da_print: fwrite failed\n");
        return -1;
    }
    return 0;
}