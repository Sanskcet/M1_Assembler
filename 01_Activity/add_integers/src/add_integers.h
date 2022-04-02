/**
 * @file add_integers.h
 * @author your name (you@domain.com)
 * @brief Header file with the required function - sum
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ADD_INTEGERS_H
#define ADD_INTEGERS_H

#include<limits.h>

typedef enum{   
    UNDERFLOW = -1,
    SUCCESS = 0,
    OVERFLOW = 1,
}func_return_type;

/**
 * @brief 
 * 
 * @param arg1 
 * @param arg2 
 * @param res 
 * @brief The function sum which checks for Overflow and Undeflow errors and returns sum if no error is found
 * @return func_return_type 
 */
func_return_type sum ( int arg1, int arg2, int* res);

#endif // ADD_INTEGERS_H
