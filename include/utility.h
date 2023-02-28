/**
 * @file utility.h
 * @author Berktug K. Ozkan (@spaceymonk)
 * @brief Utility functions declarations
 * @version 0.1
 * @date 2023-02-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UTILITY_H
#define UTILITY_H

/**
 * @brief Swaps the values of two variables
 *
 * @param a First value
 * @param b Second value
 * @param T Type of the values
 *
 */
#define SWAP(a, b, T) \
    do                \
    {                 \
        T temp = a;   \
        a = b;        \
        b = temp;     \
    } while (0)

#endif