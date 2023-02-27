#include "../include/dynamic_array.h"

#include <string.h>

da_t *da_new(size_t capacity)
{
    if (capacity == 0)
    {
        fprintf(stderr, "da_new: capacity is 0\n");
        return NULL;
    }
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

int da_free(da_t *da)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_free: da is NULL\n");
        return -1;
    }
    if (da->size > 0)
    {
        fprintf(stderr, "da_free: array is dirty\n");
        return -1;
    }
    free(da->array);
    free(da);
    return 0;
}

size_t da_size(da_t *da)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_size: da is NULL\n");
        return -1;
    }
    return da->size;
}

size_t da_capacity(da_t *da)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_capacity: da is NULL\n");
        return -1;
    }
    return da->capacity;
}

void *da_push_back(da_t *da, void *data)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_push_back: da is NULL\n");
        return NULL;
    }
    if (da->array == NULL)
    {
        fprintf(stderr, "da_push_back: array is NULL\n");
        return NULL;
    }
    if (da->size == da->capacity)
    {
        da->capacity *= 2;
        da->array = realloc(da->array, sizeof(void *) * da->capacity);
        if (da->array == NULL)
        {
            fprintf(stderr, "da_push_back: realloc failed\n");
            return NULL;
        }
    }
    da->array[da->size] = data;
    da->size++;
    return data;
}

void *da_set(da_t *da, size_t index, void *data)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_set: da is NULL\n");
        return NULL;
    }
    if (da->array == NULL)
    {
        fprintf(stderr, "da_set: array is NULL\n");
        return NULL;
    }
    if (index >= da->size)
    {
        fprintf(stderr, "da_set: index out of bounds\n");
        return NULL;
    }
    da->array[index] = data;
    return data;
}

void *da_get(da_t *da, size_t index)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_get: da is NULL\n");
        return NULL;
    }
    if (da->array == NULL)
    {
        fprintf(stderr, "da_get: array is NULL\n");
        return NULL;
    }
    if (index >= da->size)
    {
        fprintf(stderr, "da_get: index out of bounds\n");
        return NULL;
    }
    return da->array[index];
}

void *da_remove(da_t *da, size_t index)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_remove: da is NULL\n");
        return NULL;
    }
    if (da->array == NULL)
    {
        fprintf(stderr, "da_remove: array is NULL\n");
        return NULL;
    }
    if (index >= da->size)
    {
        fprintf(stderr, "da_remove: index out of bounds\n");
        return NULL;
    }
    void *data = da->array[index];
    for (size_t i = index; i < da->size - 1; i++)
    {
        da->array[i] = da->array[i + 1];
    }
    da->size--;
    return data;
}

int da_clear(da_t *da, void (*free_handler)(void *))
{
    if (da == NULL)
    {
        fprintf(stderr, "da_clear: da is NULL\n");
        return -1;
    }
    if (da->array == NULL)
    {
        fprintf(stderr, "da_clear: array is NULL\n");
        return -1;
    }
    if (free_handler != NULL)
    {
        for (size_t i = 0; i < da->size; i++)
        {
            free_handler(da->array[i]);
        }
    }
    da->size = 0;
    return 0;
}

void *da_insert(da_t *da, size_t index, void *data)
{
    if (da == NULL)
    {
        fprintf(stderr, "da_insert: da is NULL\n");
        return NULL;
    }
    if (da->array == NULL)
    {
        fprintf(stderr, "da_insert: array is NULL\n");
        return NULL;
    }
    if (index > da->size)
    {
        fprintf(stderr, "da_insert: index out of bounds\n");
        return NULL;
    }
    if (da->size == da->capacity)
    {
        da->capacity *= 2;
        da->array = realloc(da->array, sizeof(void *) * da->capacity);
        if (da->array == NULL)
        {
            fprintf(stderr, "da_insert: realloc failed\n");
            return NULL;
        }
    }
    for (size_t i = da->size; i > index; i--)
    {
        da->array[i] = da->array[i - 1];
    }
    da->array[index] = data;
    da->size++;
    return data;
}

size_t da_search(da_t *da, void *data, int (*cmp)(void *, void *))
{
    if (da == NULL)
    {
        fprintf(stderr, "da_search: da is NULL\n");
        return -1;
    }
    if (da->array == NULL)
    {
        fprintf(stderr, "da_search: array is NULL\n");
        return -1;
    }
    if (cmp == NULL)
    {
        fprintf(stderr, "da_search: cmp is NULL\n");
        return -1;
    }
    for (size_t i = 0; i < da->size; i++)
    {
        if (cmp(da->array[i], data) == 0)
        {
            return i;
        }
    }
    return -1;
}

int da_print(da_t *da, FILE *fd, char *(*to_string)(void *))
{
    if (da == NULL)
    {
        fprintf(stderr, "da_print: da is NULL\n");
        return -1;
    }
    if (da->array == NULL)
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
    for (size_t i = 0; i < da->size; i++)
    {
        char *str = to_string(da->array[i]);
        written_bytes = fwrite(str, 1, strlen(str), fd);
        if (written_bytes != strlen(str))
        {
            fprintf(stderr, "da_print: fwrite failed\n");
            return -1;
        }
        free(str);
        if (i < da->size - 1)
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