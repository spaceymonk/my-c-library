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

/* ========================================================================== */
/*                              TYPE DEFINITIONS                              */
/* ========================================================================== */

/**
 * @brief A node in the list
 *
 * @attention Do not modify this struct directly.
 *           Use the functions provided in this header.
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
 * @attention Do not modify this struct directly.
 *           Use the functions provided in this header.
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

/* ========================================================================== */
/*                             FUNCTION PROTOTYPES                            */
/* ========================================================================== */

/**
 * @brief Creates a new doubly linked list
 *
 * @note If allocation fails an error message will be printed to stderr
 *
 * @return The new list
 * @retval NULL If the allocation failed
 */
dll_t *dll_new();

/**
 * @brief Frees the list
 *
 * @param self  The list to free
 * 
 * @attention List size should be 0 prior to calling this function
 * @note If the list size is not 0, an error message will be printed to stderr
 *
 * @return  The status of the operation
 * @retval  1, If the list an error occurred
 * @retval  0, If the list is freed successfully
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
 * @note If allocation fails an error message will be printed to stderr
 *
 * @return The status of the operation
 * @retval 1, If an error occurred
 * @retval 0, If the list is printed successfully
 */
int dll_print(dll_t *self, FILE *fd, char *(*to_string)(void *));

/**
 * @brief Pushes data to the back of the list
 *
 * @param self  The list to push to
 * @param data  The data to push
 * 
 * @note If allocation fails an error message will be printed to stderr
 *
 * @return The data that was pushed
 * @retval NULL If the allocation failed
 */
void *dll_push_back(dll_t *self, void *data);

/**
 * @brief Pushes data to the front of the list
 *
 * @param self  The list to push to
 * @param data  The data to push
 *
 * @note If allocation fails an error message will be printed to stderr
 * 
 * @return The data that was pushed
 * @retval NULL If the allocation failed
 */
void *dll_push_front(dll_t *self, void *data);

/**
 * @brief Pops the last element of the list
 *
 * @param self  The list to pop from
 *
 * @note If the list is empty this function will
 *      print an error message to stderr.
 * 
 * @note If allocation fails an error message will be printed to stderr
 *
 * @return The data that was popped
 * @retval NULL If the list is empty
 */
void *dll_pop_back(dll_t *self);

/**
 * @brief Pops the first element of the list
 *
 * @note If the list is empty this function will
 *      print an error message to stderr.
 *
 * @return The data that was popped
 * @retval NULL if the list is empty
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
 *       and returns the new node
 *
 * @param self  The list to insert to
 * @param node  The node to insert after
 * @param data  The data to insert
 *
 * @return The newly created node
 * @retval NULL If an error occured
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
 * @note If an error occurs, this function will print
 *     an error message to stderr.
 *
 * @return The new node
 * @retval NULL If an error occured
 */
dll_node_t *dll_insert_before(dll_t *self, dll_node_t *node, void *data);

/**
 * @brief Removes the given node from the list
 *      and returns the data
 *
 * @param self  The list to remove from
 * @param node  The node to remove
 *
 * @note If an error occurs, this function will print
 *    an error message to stderr.
 *
 * @return The data that was removed
 * @retval NULL If an error occured
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
 * @brief Reverses the list in place and returns it
 *
 * @param self  The list to reverse
 *
 * @return `self` as a reversed list
 */
dll_t *dll_reverse(dll_t *self);

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
 * @brief Get the middle node of a linked list
 * @attention This function is not meant to be used by the user.
 *
 * @param head  head of the linked list
 *
 * @return  middle node of the linked list
 */
dll_node_t *__dll_get_middle_node(dll_node_t *head);

/**
 * @brief Merge two sorted linked lists
 * @attention This function is not meant to be used by the user.
 *
 * @param head1  head of the first sorted linked list
 * @param head2  head of the second sorted linked list
 *
 * @return  head of the merged linked list
 */
dll_node_t *__dll_merge(dll_node_t *left, dll_node_t *right,
                        int (*cmp)(void *, void *));

/**
 * @brief Merge sort a linked list from the given head
 * @attention This function is not meant to be used by the user.
 *
 * @param head  head of the linked list
 *
 * @return  head of the sorted linked list
 */
dll_node_t *__dll_sort(dll_node_t *head, int (*cmp)(void *, void *));

#endif