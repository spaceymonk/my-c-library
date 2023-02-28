/**
 * @file utiliy.c
 * @author Berktug K. Ozkan (@spaceymonk)
 * @brief Implementation of utility functions
 * @version 0.1
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../include/utility.h"

void swap(void **a, void **b)
{
    void *temp = *a;
    *a = *b;
    *b = temp;
}
