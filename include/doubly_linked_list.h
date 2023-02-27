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
 * @return The new list
 * @retval NULL If the allocation failed
 */
dll_t *dll_new();

/**
 * @brief Frees the list
 *
 * @param dll  The list to free
 * 
 * @attention List size should be 0 prior to calling this function
 *
 * @return  The status of the operation
 * @retval -1, If the list an error occurred
 * @retval  0, If the list is freed successfully
 */
int dll_free(dll_t *dll);

/**
 * @brief Get the size of the list
 * 
 * @param dll  The list to get the size of
 * 
 * @return The size of the list
 * @retval -1 If an error occurred
 */
size_t dll_size(dll_t *dll);

/**
 * @brief Prints the list to given file descriptor
 *
 * @param dll The list to print
 * @param fd The file descriptor to print to
 * @param to_string A function that converts the data to string
 *                 to be printed. This function should return
 *                 a pointer to a string that is allocated on
 *                 the heap. The `dll_print` function will free
 *                 the string after printing it.
 *
 * @return The status of the operation
 * @retval -1, If an error occurred
 * @retval 0, If the list is printed successfully
 */
int dll_print(dll_t *dll, FILE *fd, char *(*to_string)(void *));

/**
 * @brief Pushes data to the back of the list
 *
 * @param dll  The list to push to
 * @param data  The data to push
 * 
 * @return The data that was pushed
 * @retval NULL If the allocation failed
 */
void *dll_push_back(dll_t *dll, void *data);

/**
 * @brief Pushes data to the front of the list
 *
 * @param dll  The list to push to
 * @param data  The data to push
 *
 * @return The data that was pushed
 * @retval NULL If the allocation failed
 */
void *dll_push_front(dll_t *dll, void *data);

/**
 * @brief Pops the last element of the list
 *
 * @param dll  The list to pop from
 *
 * @return The data that was popped
 * @retval NULL If the list is empty
 */
void *dll_pop_back(dll_t *dll);

/**
 * @brief Pops the first element of the list
 *
 * @return The data that was popped
 * @retval NULL if the list is empty
 */
void *dll_pop_front(dll_t *dll);

/**
 * @brief Clears the list and transforms it into initial state
 *
 * @param dll          The list to clear
 * @param free_handler  The function to free the data. This
 *                     param can be NULL if the data does
 *                     not need to be freed. But user should
 *                     make sure that the data is freed
 *                     before the list is freed.
 *
 * @return The status of the operation
 * @retval -1, If an error occurred
 * @retval 0, If the list is cleared successfully
 */
int dll_clear(dll_t *dll, void (*free_handler)(void *));

/**
 * @brief Inserts data after the given node
 *       and returns the new node
 *
 * @param dll  The list to insert to
 * @param node  The node to insert after
 * @param data  The data to insert
 *
 * @return The newly created node
 * @retval NULL If an error occured
 */
dll_node_t *dll_insert_after(dll_t *dll, dll_node_t *node, void *data);

/**
 * @brief Inserts data before the given node
 *      and returns the new node
 *
 * @param dll  The list to insert to
 * @param node  The node to insert before
 * @param data  The data to insert
 *
 * @return The new node
 * @retval NULL If an error occured
 */
dll_node_t *dll_insert_before(dll_t *dll, dll_node_t *node, void *data);

/**
 * @brief Removes the given node from the list
 *      and returns the data
 *
 * @param dll  The list to remove from
 * @param node  The node to remove
 *
 * @return The data that was removed
 * @retval NULL If an error occured
 */
void *dll_remove(dll_t *dll, dll_node_t *node);

/**
 * @brief Search for the given data in the list
 *       and returns the first node that contains it
 *
 * @param dll  The list to search in
 * @param data  The data to search for
 * @param cmp   The comparison function to compare the data
 *
 * @return The node that contains the data
 * @retval NULL If the data is not found
 * @retval NULL If an error occured
 */
dll_node_t *dll_search(dll_t *dll, void *data, int (*cmp)(void *, void *));

/**
 * @brief Reverses the list in place and returns it
 *
 * @param dll  The list to reverse
 *
 * @return `dll` as a reversed list
 */
dll_t *dll_reverse(dll_t *dll);

/**
 * @brief Sorts the list in place using the given comparision
 *       function and returns the sorted list
 *
 * @param dll  The list to sort
 * @param cmp   The comparison function to compare the data
 *
 * @note The comparasion function should return 0 if the
 *      data is equal, negative if the first data is less
 *      than the second, and positive otherwise.
 *
 * @note This function uses the merge sort algorithm.
 *
 * @return `dll` as a sorted list
 * @retval NULL If an error occured
 */
dll_t *dll_sort(dll_t *dll, int (*cmp)(void *, void *));

/**
 * @brief Get the middle node of a linked list
 * @attention This function is not meant to be used by the user.
 *
 * @param head  head of the linked list
 *
 * @return  middle node of the linked list
 * @retval  NULL, if head is NULL
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