/**
 * @file dynamic_array.h
 * @author Berktug K. Ozkan (@spaceymonk)
 * @brief Dynamic Array interface
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

/* ========================================================================== */
/*                              TYPE DEFINITIONS                              */
/* ========================================================================== */

/**
 * @brief A dynamic array structure
 *
 * @attention Do not modify this struct directly.
 *          Use the functions provided in this header.
 *
 * @param array     The array
 * @param size      The size of the array
 * @param capacity  The capacity of the array
 */
typedef struct da
{
    void **array;
    size_t size;
    size_t capacity;
} da_t;

/* ========================================================================== */
/*                             FUNCTION PROTOTYPES                            */
/* ========================================================================== */

/**
 * @brief Create a dynamic array
 *
 * @param capacity  Initial capacity of the array
 *
 * @return        A pointer to the dynamic array
 * @retval NULL   If the allocation failed
 */
da_t *da_new(size_t capacity);

/**
 * @brief Free the dynamic array
 *
 * @param da  The dynamic array
 *
 * @attention  This function does not free the data in the array. It only frees
 *           the array itda.
 *
 * @return        operation status
 * @retval 0      If the operation was successful
 * @retval -1     If the operation failed
 */
int da_free(da_t *da);

/**
 * @brief Get the size of the array
 *
 * @param da  The dynamic array
 *
 * @return  size of the array
 * @retval -1  If the operation failed
 */
size_t da_size(da_t *da);

/**
 * @brief Get the size of the capacity
 *
 * @param da  The dynamic array
 *
 * @return  capacity of the array
 * @retval -1  If the operation failed
 */

/**
 * @brief Add an element to the end of the array
 *
 * @param da  The dynamic array
 * @param data  The data to be added
 *
 * @return data that was added
 * @retval NULL   If the operation failed
 */
void *da_push_back(da_t *da, void *data);

/**
 * @brief Updates the element at the given index
 *
 * @param da  The dynamic array
 * @param index The index of the element to be updated
 * @param data  The data to be updated
 *
 * @return  previous data at the given index
 * @retval  NULL    If the operation failed
 */
void *da_set(da_t *da, size_t index, void *data);

/**
 * @brief Get the element at the given index
 *
 * @param da  The dynamic array
 * @param index The index of the element to be retrieved
 *
 * @return  data at the given index
 * @retval  NULL    If the operation failed
 */
void *da_get(da_t *da, size_t index);

/**
 * @brief Remove the element at the given index
 *
 * @param da  The dynamic array
 * @param index The index of the element to be removed
 *
 * @return  data at the given index
 * @retval  NULL    If the operation failed
 */
void *da_remove(da_t *da, size_t index);

/**
 * @brief Clears the array
 *
 * @param da          The list to clear
 * @param free_handler  The function to free the data. This
 *                     param can be NULL if the data does
 *                     not need to be freed. But user should
 *                     make sure that the data is freed
 *                     before the list is freed.
 *
 * @return       operation status
 * @retval 0     If the operation was successful
 * @retval -1    If the operation failed
 */
int da_clear(da_t *da, void (*free_handler)(void *));

/**
 * @brief Inserts an element at the given index
 *
 * @param da  The dynamic array
 * @param index The index of the element to be inserted
 * @param data  The data to be inserted
 *
 * @return  data that was inserted
 * @retval  NULL    If the operation failed
 */
void *da_insert(da_t *da, size_t index, void *data);

/**
 * @brief Search for the given data in the array
 *
 * @param da  The dynamic array
 * @param data  The data to be searched
 * @param cmp   The comparison function, which should return 0 if the data is
 *             found
 *
 * @return  index of the data
 * @retval  -1  If the data is not found
 */
size_t da_search(da_t *da, void *data, int (*cmp)(void *, void *));

/**
 * @brief Search for the given data in the array using binary search
 *
 * @attention The array must be sorted before using this function
 *
 * @param da  The dynamic array
 * @param data  The data to be searched
 * @param cmp   The comparison function, which should return 0 if the data is
 *           found, -1 if the data is less than the element in the array, and 1
 *          if the data is greater than the element in the array
 *
 * @return  index of the data
 * @retval  -1  If the data is not found
 */
size_t da_binary_search(da_t *da, void *data, int (*cmp)(void *, void *));

/**
 * @brief Sort the array in place using the given comparison function
 *
 * @param da  The dynamic array
 * @param cmp   The comparison function, which should return -1 if the first
 *            element is less than the second, 0 if they are equal, and 1 if the
 *            first element is greater than the second
 *
 * @note This function uses quicksort algorithm.
 *
 * @return `da` as a sorted array
 */
da_t *da_sort(da_t *da, int (*cmp)(void *, void *));

/**
 * @brief Sort the array in place using the given comparison function
 *
 * @details This function is used internally by `da_sort` and should not be used
 *         by the user. The user should use `da_sort` instead. This function
 *         quicksort algorithm.
 * @see da_sort
 *
 * @attention This function is not meant to be used by the user.
 *
 * @param array The array to be sorted
 * @param size  The size of the array
 * @param cmp   The comparison function as described in `da_sort`
 *
 * @return `array` as a sorted array
 */
void **__da_sort(void **array, size_t size, int (*cmp)(void *, void *));

/**
 * @brief Reverses the array in place
 *
 * @param da  The dynamic array
 *
 * @return `da` as a reversed array
 */
da_t *da_reverse(da_t *da);

/**
 * @brief Shrinks the capacity of the array to the size of the array
 *
 * @details This function is useful when the array is not going to be used
 *         for a while and the memory can be freed.
 *
 * @param da  The dynamic array
 *
 * @return `da` as a shrunk array
 */
da_t *da_shrink(da_t *da);

/**
 * @brief Prints the array to the given file descriptior
 *
 * @param da  The dynamic array
 * @param fd    The file descriptor
 * @param to_string The function to convert the data to string
 *
 * @return The status of the operation
 * @retval -1, If an error occurred
 * @retval 0, If the list is printed successfully
 */
int da_print(da_t *da, FILE *fd, char *(*to_string)(void *));

#endif