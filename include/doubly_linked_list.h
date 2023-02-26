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

#include <stdio.h>
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
 * @brief Clears the list and frees all nodes by
 *       calling the free function on the data
 *
 * @param self          The list to clear
 * @param free_handler  The function to free the data. This
 *                     param can be NULL if the data does
 *                     not need to be freed. But user should
 *                     make sure that the data is freed
 *                     before the list is freed.
 *
 * @return void
 */
void dll_clear(dll_t *self, void (*free_handler)(void *));

/**
 * @brief Inserts data after the given node
 *      and returns the new node
 * 
 * @param self  The list to insert to
 * @param node  The node to insert after
 * @param data  The data to insert
 * 
 * @return The new node, NULL if an error occured
*/
dll_node_t *dll_insert_after(dll_t *self, dll_node_t *node, void *data);

/**
 * @brief Inserts data before the given node
 *      and returns the new node
 * 
 * @param self  The list to insert to
 * @param node  The node to insert before
 * @param data  The data to insert
 * 
 * @return The new node, NULL if an error occured
*/
dll_node_t *dll_insert_before(dll_t *self, dll_node_t *node, void *data);

/**
 * @brief Removes the given node from the list
 *      and returns the data
 *
 * @param self  The list to remove from
 * @param node  The node to remove
 *
 * @return The data that was removed, NULL if an error occured
 */
void *dll_remove(dll_t *self, dll_node_t *node);

/**
 * @brief Search for the given data in the list
 *       and returns the first node that contains it
 *
 * @param self  The list to search in
 * @param data  The data to search for
 * @param cmp   The comparison function to compare the data
 *
 * @note The comparasion function should return 0 if the
 *      data is equal.
 *
 * @return The node that contains the data, NULL if not found
 */
dll_node_t *dll_search(dll_t *self, void *data, int (*cmp)(void *, void *));

/**
 * @brief Sorts the list in place using the given comparision
 *       function and returns the sorted list
 *
 * @param self  The list to sort
 * @param cmp   The comparison function to compare the data
 *
 * @note The comparasion function should return 0 if the
 *      data is equal, negative if the first data is less
 *      than the second, and positive otherwise.
 *
 * @note This function uses the merge sort algorithm.
 *
 * @return `self` as a sorted list
 */
dll_t *dll_sort(dll_t *self, int (*cmp)(void *, void *));

/**
 * @brief Reverses the list in place and returns it
 * 
 * @param self  The list to reverse
 * 
 * @return `self` as a reversed list
 */
dll_t *dll_reverse(dll_t *self);

#endif