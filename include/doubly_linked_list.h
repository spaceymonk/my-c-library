/**
 * @file doubly_linked_list.h
 * @author Berktug K. Ozkan (@spaceymonk)
 * @brief Doubly linked list interface
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include<stdio.h>
#include <stdlib.h>

/**
 * @brief A node in the list
 *
 * @param data  The data stored in the node
 * @param next  The next node in the list
 * @param prev  The previous node in the list
 */
typedef struct dll_node
{
    void *data;
    struct dll_node *next;
    struct dll_node *prev;
} dll_node_t;

/**
 * @brief A doubly linked list structure
 *
 * @param head  The head of the list
 * @param tail  The tail of the list
 * @param size  The size of the list
 */
typedef struct dll
{
    dll_node_t *head;
    dll_node_t *tail;
    size_t size;
} dll_t;

/**
 * @brief Creates a new doubly linked list
 *
 * @return The new list
 */
dll_t *dll_new();

/**
 * @brief Frees the list
 *
 * @param self  The list to free
 *
 * @return 1 on failure, 0 on success
 */
int dll_free(dll_t *self);

/**
 * @brief Prints the list to given file descriptor
 *
 * @param self The list to print
 * @param fd The file descriptor to print to
 * @param to_string A function that converts the data to string
 *                 to be printed. This function should return
 *                 a pointer to a string that is allocated on
 *                 the heap. The `dll_print` function will free
 *                 the string after printing it.
 * 
 * @return void
 */
void dll_print(dll_t *self, FILE *fd, char *(*to_string)(void *));

/**
 * @brief Pushes data to the back of the list
 *
 * @param self  The list to push to
 * @param data  The data to push
 *
 * @return The data that was pushed
 */
void *dll_push_back(dll_t *self, void *data);

/**
 * @brief Pushes data to the front of the list
 *
 * @param self  The list to push to
 * @param data  The data to push
 *
 * @return The data that was pushed
 */
void *dll_push_front(dll_t *self, void *data);

/**
 * @brief Pops the last element of the list
 *
 * @param self  The list to pop from
 *
 * @note If the list is empty this function will
 *      return NULL and print an error message to
 *      stderr.
 *
 * @return The data that was popped,
 *        NULL if the list is empty
 */
void *dll_pop_back(dll_t *self);

/**
 * @brief Pops the first element of the list
 *
 * @note If the list is empty this function will
 *      return NULL and print an error message to
 *      stderr.
 *
 * @return The data that was popped,
 *        NULL if the list is empty
 */
void *dll_pop_front(dll_t *self);

/**
 * @brief Inserts data at the given index
 *
 * @param self   The list to insert into
 * @param data   The data to insert
 * @param index  The index to insert at
 *
 * @return The data that was inserted
 */
void *dll_insert(dll_t *self, void *data, size_t index);

/**
 * @brief Removes the element at the given index
 *       and returns it
 *
 * @note This function does not free the data that
 *      was removed. It is up to the user to free
 *      the data if needed.
 *
 * @param self   The list to remove from
 * @param index  The index to remove at
 *
 * @return The data that was removed
 */
void *dll_remove(dll_t *self, size_t index);

/**
 * @brief Gets the data at the given index
 *
 * @param self   The list to get from
 * @param index  The index to get at
 *
 * @return The data at the given index
 */
void *dll_get(dll_t *self, size_t index);

/**
 * @brief Sets the data at the given index
 *
 * @param self   The list to set in
 * @param data   The data to set
 * @param index  The index to set at
 *
 * @return The data that was replaced
 */
void *dll_set(dll_t *self, void *data, size_t index);

/**
 * @brief Clears the list and frees all nodes by
 *      calling the free function on the data
 *
 * @param self          The list to clear
 * @param free_handler  The function to free the data
 *
 * @return void
 */
void dll_clear(dll_t *self, void (*free_handler)(void *));

#endif